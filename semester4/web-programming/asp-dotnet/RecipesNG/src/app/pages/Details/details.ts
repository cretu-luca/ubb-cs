import { Component, OnInit, ViewChild } from '@angular/core';
import { ActivatedRoute, Router } from '@angular/router';
import { CommonModule } from '@angular/common';
import { HttpClient } from '@angular/common/http';
import { UpdateRecipeInputFormComponent } from '../../components/update-recipe-input-form/update-recipe-input-form.component';

interface Recipe {
  recipeID: string;
  name: string;
  author: string;
  type: string;
  instructions: string;
  date: string;
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
    this.http.get<Recipe>(`https://localhost:7269/Recipe/GetById/${this.recipeId}`)
      .subscribe({
        next: (data) => {
          this.recipe = data;
          if (this.recipe) {
            this.loadIngredients(this.recipe.recipeID);
          }
        },
        error: (error) => {
          console.error("Failed to fetch recipe details:", error);
        }
      });
  }

  loadIngredients(recipeId: string): void {
    this.http.get<any[]>(
      `https://localhost:7269/Ingredient/GetIngredientsByRecipeId/${recipeId}`
    ).subscribe({
      next: (data) => {
        if (Array.isArray(data)) {
          this.ingredients = data
            .map((ingredient: any) => 
              `${ingredient.name}: ${ingredient.quantity} ${ingredient.measurementUnit}`
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
        updatedRecipe.recipeID = this.recipeId;
        
        this.http.put<Recipe>(
          "https://localhost:7269/Recipe/Update",
          updatedRecipe
        ).subscribe({
          next: (data) => {
            alert("Recipe updated successfully!");
            this.editMode = false;
            this.recipe = data;
          },
          error: (error) => {
            console.error("Error updating recipe:", error);
            alert("Error updating recipe. Please try again.");
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
      this.http.delete(
        `https://localhost:7269/Recipe/Delete/${this.recipeId}`
      ).subscribe({
        next: () => {
          alert("Recipe deleted successfully!");
          this.router.navigate(['/browse']);
        },
        error: (error) => {
          console.error("Error deleting recipe:", error);
          alert("Error deleting recipe. Please try again.");
        }
      });
    }
  }

  onAddIngredientClick(): void {
    this.router.navigate(['/add-ingredient'], { 
      queryParams: { 
        recipeID: this.recipeId,
        recipeName: this.recipe?.name || ''
      }
    });
  }
} 