import { Component, OnInit, AfterViewInit } from '@angular/core';
import { ActivatedRoute, Router } from '@angular/router';
import { CommonModule } from '@angular/common';
import { RecipeInputFormComponent } from '../../components/recipe-input-form/recipe-input-form.component';
import { HttpClient } from '@angular/common/http';

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
  imports: [CommonModule, RecipeInputFormComponent],
  templateUrl: './details.html',
  styleUrl: './details.css'
})
export class DetailsComponent implements OnInit, AfterViewInit {
  recipeId: string = '';
  ingredients: string = '';
  editMode: boolean = false;
  
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
  
  ngAfterViewInit(): void {
    this.setFormReadOnly(true);
    const addIngredientButton = document.getElementById('add-ingredient-button') as HTMLButtonElement;
    if (addIngredientButton) {
      addIngredientButton.style.display = 'none';
    }
  }
  
  setFormReadOnly(isReadOnly: boolean): void {
    // Using direct DOM manipulation
    const nameInput = document.getElementById('name') as HTMLInputElement;
    const authorInput = document.getElementById('author') as HTMLInputElement;
    const typeInput = document.getElementById('type') as HTMLInputElement;
    const dateInput = document.getElementById('date') as HTMLInputElement;
    const instructionsInput = document.getElementById('instructions') as HTMLTextAreaElement;
    
    if (nameInput && authorInput && typeInput && dateInput && instructionsInput) {
      nameInput.readOnly = isReadOnly;
      authorInput.readOnly = isReadOnly;
      typeInput.readOnly = isReadOnly;
      dateInput.readOnly = isReadOnly;
      instructionsInput.readOnly = isReadOnly;
    }
  }

  loadRecipeData(): void {
    this.http.get<ApiResponse>(`http://localhost:8000/API/recipes.php?action=getByID&id=${this.recipeId}`)
      .subscribe({
        next: (data) => {
          if (data.success && data.data) {
            const recipe = data.data;
            
            // Using direct DOM manipulation
            const nameInput = document.getElementById('name') as HTMLInputElement;
            const authorInput = document.getElementById('author') as HTMLInputElement;
            const typeInput = document.getElementById('type') as HTMLInputElement;
            const dateInput = document.getElementById('date') as HTMLInputElement;
            const instructionsInput = document.getElementById('instructions') as HTMLTextAreaElement;
            
            if (nameInput && authorInput && typeInput && dateInput && instructionsInput) {
              nameInput.value = recipe.Name;
              authorInput.value = recipe.Author;
              typeInput.value = recipe.Type;
              dateInput.value = recipe.Date;
              instructionsInput.value = recipe.Instructions;
            }
            
            this.loadIngredients(recipe.RecipeID);
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
          const ingredientsText = data.data
            .map((ingredient: any) => 
              `${ingredient.Name}: ${ingredient.Quantity} ${ingredient.MeasurementUnit}`
            )
            .join("\n");
            
          // Set ingredients textarea value
          const ingredientsTextarea = document.getElementById('ingredients') as HTMLTextAreaElement;
          if (ingredientsTextarea) {
            ingredientsTextarea.value = ingredientsText;
            this.ingredients = ingredientsText;
          }
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
      this.setFormReadOnly(false);
      
      // Update button text and color
      const updateButton = document.getElementById('update-button') as HTMLButtonElement;
      if (updateButton) {
        updateButton.textContent = 'Save';
        updateButton.style.color = 'red';
      }
      
      // Show the add ingredient button in edit mode
      const addIngredientButton = document.getElementById('add-ingredient-button') as HTMLButtonElement;
      if (addIngredientButton) {
        addIngredientButton.style.display = '';
      }
    } else {
      // Get form values directly from DOM
      const nameInput = document.getElementById('name') as HTMLInputElement;
      const authorInput = document.getElementById('author') as HTMLInputElement;
      const typeInput = document.getElementById('type') as HTMLInputElement;
      const dateInput = document.getElementById('date') as HTMLInputElement;
      const instructionsInput = document.getElementById('instructions') as HTMLTextAreaElement;
      
      // Validate form
      if (nameInput.value && authorInput.value && typeInput.value && dateInput.value && instructionsInput.value) {
        const updatedRecipe = {
          RecipeID: this.recipeId,
          Name: nameInput.value,
          Author: authorInput.value,
          Type: typeInput.value,
          Instructions: instructionsInput.value,
          Date: dateInput.value
        };

        this.http.put<ApiResponse>(
          "http://localhost:8000/API/recipes.php?action=update",
          updatedRecipe
        ).subscribe({
          next: (data) => {
            if (data.success) {
              alert("Recipe updated successfully!");
              this.editMode = false;
              this.setFormReadOnly(true);
              
              // Reset button text and color
              const updateButton = document.getElementById('update-button') as HTMLButtonElement;
              if (updateButton) {
                updateButton.textContent = 'Update';
                updateButton.style.color = '';
              }
              
              // Hide the add ingredient button in view mode
              const addIngredientButton = document.getElementById('add-ingredient-button') as HTMLButtonElement;
              if (addIngredientButton) {
                addIngredientButton.style.display = 'none';
              }
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
    // Get recipe name from DOM
    const nameInput = document.getElementById('name') as HTMLInputElement;
    const recipeName = nameInput ? nameInput.value : '';
    
    this.router.navigate(['/add-ingredient'], { 
      queryParams: { 
        RecipeID: this.recipeId,
        recipeName: recipeName
      }
    });
  }
} 