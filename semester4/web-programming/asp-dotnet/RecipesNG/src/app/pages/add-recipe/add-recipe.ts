import { Component, ViewChild } from '@angular/core';
import { CommonModule } from '@angular/common';
import { RouterLink } from '@angular/router';
import { RecipeInputFormComponent } from '../../components/recipe-input-form/recipe-input-form.component';
import { HttpClient } from '@angular/common/http';

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

  constructor(private http: HttpClient) {}

  handleSubmit(): void {
    if (!this.recipeFormComponent.isValid()) {
      alert('Please fill all fields');
      return;
    }

    const recipe = this.recipeFormComponent.getFormData();

    this.http
      .post<Recipe>('https://localhost:7269/Recipe/Create', recipe)
      .subscribe({
        next: (data) => {
          alert('Recipe added successfully!');
          this.recipeFormComponent.reset();
        },
        error: (error) => {
          alert('Error adding recipe. Please try again.');
        },
      });
  }
}
