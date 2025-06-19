import { Component, ViewChild } from '@angular/core';
import { CommonModule } from '@angular/common';
import { RouterLink, Router } from '@angular/router';
import { RecipeInputFormComponent } from '../../components/recipe-input-form/recipe-input-form.component';
import { HttpClient, HttpErrorResponse } from '@angular/common/http';

interface Recipe {
  recipeID: string;
  name: string;
  author: string;
  type: string;
  instructions: string;
  date: string;
}

@Component({
  selector: 'add-recipe',
  standalone: true,
  imports: [CommonModule, RouterLink, RecipeInputFormComponent],
  templateUrl: './add-recipe.html',
  styleUrl: './add-recipe.css',
})
export class AddRecipe {
  @ViewChild(RecipeInputFormComponent)
  recipeFormComponent!: RecipeInputFormComponent;
  errorMessage: string = '';

  constructor(private http: HttpClient) {}

  handleSubmit(): void {
    this.errorMessage = '';
    
    if (!this.recipeFormComponent.isValid()) {
      this.errorMessage = 'Please fill all fields';
      return;
    }

    const recipe = this.recipeFormComponent.getFormData();

    this.http
      .post<Recipe>('https://localhost:7269/Recipe/Create', recipe, {
        withCredentials: true
      })
      .subscribe({
        next: (data) => {
          alert('Recipe added successfully!');
          this.recipeFormComponent.reset();
        },
        error: (error) => {
          this.handleError(error);
        },
      });
  }
  
  private handleError(error: HttpErrorResponse): void {
    if (error.status === 401) {
      this.errorMessage = 'You need to be logged in to add recipes.';
    } else {
      this.errorMessage = 'Error adding recipe. Please try again.';
    }
  }
}
