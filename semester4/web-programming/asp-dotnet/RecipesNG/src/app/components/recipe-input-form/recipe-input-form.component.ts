import { Component } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';

export interface RecipeFormData {
  name: string;
  author: string;
  type: string;
  instructions: string;
  date: string;
}

@Component({
  selector: 'app-recipe-input-form',
  standalone: true,
  imports: [CommonModule, FormsModule],
  templateUrl: './recipe-input-form.component.html',
  styleUrl: './recipe-input-form.component.css'
})
export class RecipeInputFormComponent {
  name: string = '';
  author: string = '';
  type: string = '';
  instructions: string = '';
  date: string = '';

  getFormData(): RecipeFormData {
    return {
      name: this.name,
      author: this.author,
      type: this.type,
      instructions: this.instructions,
      date: this.date
    };
  }

  isValid(): boolean {
    return !!(this.name && this.author && this.type && this.instructions && this.date);
  }

  reset(): void {
    this.name = '';
    this.author = '';
    this.type = '';
    this.instructions = '';
    this.date = '';
  }
}
