import { Component, ViewChild } from '@angular/core';
import { CommonModule } from '@angular/common';
import { RouterLink } from '@angular/router';
import { RecipeInputFormComponent } from '../../components/recipe-input-form/recipe-input-form.component';
import { HttpClient } from '@angular/common/http';

@Component({
  selector: 'add-recipe',
  standalone: true,
  imports: [CommonModule, RouterLink, RecipeInputFormComponent],
  templateUrl: './add-recipe.html',
  styleUrl: './add-recipe.css',
})
export class AddRecipe {
  @ViewChild(RecipeInputFormComponent) recipeFormComponent!: RecipeInputFormComponent;

  constructor(private http: HttpClient) {}

  handleSubmit(): void {
    if (!this.recipeFormComponent.isValid()) {
      alert('Please fill all fields');
      return;
    }

    const recipe = this.recipeFormComponent.getFormData();

    this.http.post<{success: boolean, data: string}>('http://localhost:8000/API/recipes.php?action=create', recipe)
      .subscribe({
        next: (data) => {
          if (data.success) {
            alert('Recipe added successfully!');
            this.recipeFormComponent.reset();
          } else {
            alert('Error: ' + data.data);
          }
        },
        error: (error) => {
          alert('Error adding recipe. Please try again.');
        }
      });
  }
}
