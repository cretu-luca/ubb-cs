import { Component, Input, Output, EventEmitter } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';

@Component({
  selector: 'app-update-recipe-input-form',
  standalone: true,
  imports: [CommonModule, FormsModule],
  templateUrl: './update-recipe-input-form.component.html',
  styleUrls: ['./update-recipe-input-form.component.css']
})
export class UpdateRecipeInputFormComponent {
  @Input() recipe: any = {};
  @Input() ingredients: string = '';
  @Input() readOnly: boolean = true;
  @Output() recipeChange = new EventEmitter<any>();

  
  recipeName: string = '';
  recipeAuthor: string = '';
  recipeType: string = '';
  recipeDate: string = '';
  recipeInstructions: string = '';

  ngOnChanges() {
    if (this.recipe) {
      this.recipeName = this.recipe.Name || '';
      this.recipeAuthor = this.recipe.Author || '';
      this.recipeType = this.recipe.Type || '';
      this.recipeDate = this.recipe.Date || '';
      this.recipeInstructions = this.recipe.Instructions || '';
    }
  }

  updateRecipe() {
    if (!this.readOnly) {
      const updatedRecipe = { ...this.recipe };
      updatedRecipe.Name = this.recipeName;
      updatedRecipe.Author = this.recipeAuthor;
      updatedRecipe.Type = this.recipeType;
      updatedRecipe.Date = this.recipeDate;
      updatedRecipe.Instructions = this.recipeInstructions;
      this.recipeChange.emit(updatedRecipe);
    }
  }

  isValid(): boolean {
    return !!(this.recipeName && this.recipeAuthor && this.recipeType && 
              this.recipeDate && this.recipeInstructions);
  }

  getFormData(): any {
    return {
      RecipeID: this.recipe?.RecipeID || null,
      Name: this.recipeName,
      Author: this.recipeAuthor,
      Type: this.recipeType,
      Date: this.recipeDate,
      Instructions: this.recipeInstructions
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
