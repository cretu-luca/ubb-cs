import { Component, OnInit, ViewChild } from '@angular/core';
import { ActivatedRoute, Router } from '@angular/router';
import { CommonModule } from '@angular/common';
import { HttpClient } from '@angular/common/http';
import { UpdateRecipeInputFormComponent } from '../../components/update-recipe-input-form/update-recipe-input-form.component';

interface Recipe {
  RecipeID: string;
  Name: string;
  Author: string;
  Type: string;
  Instructions: string;
  Date: string;
}

interface ApiResponse {
  success: boolean;
  data: any;
}

@Component({
  selector: 'recipe-details',
  standalone: true,
  imports: [CommonModule, UpdateRecipeInputFormComponent],
  templateUrl: './details.html',
  styleUrls: ['./details.css']
})
export class DetailsComponent implements OnInit {
  recipeId: string = '';
  recipe: Recipe | null = null;
  ingredients: string = '';
  editMode: boolean = false;
  
  @ViewChild(UpdateRecipeInputFormComponent) formComponent!: UpdateRecipeInputFormComponent;
  
  constructor(
    private route: ActivatedRoute, 
    private router: Router,
    private http: HttpClient
  ) {}

  ngOnInit(): void {
    this.route.paramMap.subscribe(params => {
      this.recipeId = params.get('id') || '';
      if (this.recipeId) {
        this.loadRecipeData();
      }
    });
  }
  
  loadRecipeData(): void {
    this.http.get<ApiResponse>(`http://localhost:8000/API/recipes.php?action=getByID&id=${this.recipeId}`)
      .subscribe({
        next: (data) => {
          if (data.success && data.data) {
            this.recipe = data.data;
            if (this.recipe) {
              this.loadIngredients(this.recipe.RecipeID);
            }
          }
        },
        error: (error) => {
          console.error("Failed to fetch recipe details:", error);
        }
      });
  }

  loadIngredients(recipeId: string): void {
    this.http.get<ApiResponse>(
      `http://localhost:8000/API/ingredients.php?action=getIngredientsByRecipeId&recipeId=${recipeId}`
    ).subscribe({
      next: (data) => {
        if (data.success && data.data) {
          this.ingredients = data.data
            .map((ingredient: any) => 
              `${ingredient.Name}: ${ingredient.Quantity} ${ingredient.MeasurementUnit}`
            )
            .join("\n");
        }
      },
      error: (error) => {
        console.error("Failed to fetch ingredients:", error);
      }
    });
  }

  onUpdateClick(): void {
    if (!this.editMode) {
      this.editMode = true;
    } else {
      if (this.formComponent.isValid()) {
        const updatedRecipe = this.formComponent.getFormData();
        updatedRecipe.RecipeID = this.recipeId;
        
        this.http.put<ApiResponse>(
          "http://localhost:8000/API/recipes.php?action=update",
          updatedRecipe
        ).subscribe({
          next: (data) => {
            if (data.success) {
              alert("Recipe updated successfully!");
              this.editMode = false;
              this.recipe = updatedRecipe;
            } else {
              alert("Failed to update recipe: " + (data.data || "Unknown error"));
            }
          },
          error: (error) => {
            console.error("Error updating recipe:", error);
            alert("Error updating recipe: " + error);
          }
        });
      } else {
        alert("Please fill all required fields");
      }
    }
  }

  onRecipeChange(updatedRecipe: Recipe): void {
    if (this.editMode) {
      this.recipe = updatedRecipe;
    }
  }

  onDeleteClick(): void {
    if (confirm("Are you sure you want to delete this recipe?")) {
      this.http.delete<ApiResponse>(
        `http://localhost:8000/API/recipes.php?action=delete&id=${this.recipeId}`
      ).subscribe({
        next: (data) => {
          if (data.success) {
            alert("Recipe deleted successfully!");
            this.router.navigate(['/browse']);
          } else {
            alert("Failed to delete recipe: " + (data.data || "Unknown error"));
          }
        },
        error: (error) => {
          console.error("Error deleting recipe:", error);
          alert("Error deleting recipe: " + error);
        }
      });
    }
  }

  onAddIngredientClick(): void {
    this.router.navigate(['/add-ingredient'], { 
      queryParams: { 
        RecipeID: this.recipeId,
        recipeName: this.recipe?.Name || ''
      }
    });
  }
} 