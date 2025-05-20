import { Component, Input, Output, EventEmitter } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';

interface Recipe {
  recipeID: string;
  name: string;
  author: string;
  type: string;
  instructions: string;
  date: string;
}

@Component({
  selector: 'app-update-recipe-input-form',
  standalone: true,
  imports: [CommonModule, FormsModule],
  templateUrl: './update-recipe-input-form.component.html',
  styleUrls: ['./update-recipe-input-form.component.css']
})
export class UpdateRecipeInputFormComponent {
  @Input() recipe: Recipe | null = null;
  @Input() ingredients: string = '';
  @Input() readOnly: boolean = true;
  @Output() recipeChange = new EventEmitter<Recipe>();
  
  recipeName: string = '';
  recipeAuthor: string = '';
  recipeType: string = '';
  recipeDate: string = '';
  recipeInstructions: string = '';

  ngOnChanges() {
    if (this.recipe) {
      this.recipeName = this.recipe.name || '';
      this.recipeAuthor = this.recipe.author || '';
      this.recipeType = this.recipe.type || '';
      this.recipeDate = this.recipe.date || '';
      this.recipeInstructions = this.recipe.instructions || '';
    }
  }

  updateRecipe() {
    if (!this.readOnly && this.recipe) {
      const updatedRecipe = { ...this.recipe };
      updatedRecipe.name = this.recipeName;
      updatedRecipe.author = this.recipeAuthor;
      updatedRecipe.type = this.recipeType;
      updatedRecipe.date = this.recipeDate;
      updatedRecipe.instructions = this.recipeInstructions;
      this.recipeChange.emit(updatedRecipe);
    }
  }

  isValid(): boolean {
    return !!(this.recipeName && this.recipeAuthor && this.recipeType && 
              this.recipeDate && this.recipeInstructions);
  }

  getFormData(): Recipe {
    return {
      recipeID: this.recipe?.recipeID || '',
      name: this.recipeName,
      author: this.recipeAuthor,
      type: this.recipeType,
      date: this.recipeDate,
      instructions: this.recipeInstructions
    };
  }

  reset(): void {
    this.recipeName = '';
    this.recipeAuthor = '';
    this.recipeType = '';
    this.recipeDate = '';
    this.recipeInstructions = '';
  }
}
