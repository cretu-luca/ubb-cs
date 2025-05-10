import { Component, OnInit } from '@angular/core';
import { CommonModule } from '@angular/common';
import { RouterLink } from '@angular/router';

@Component({
  selector: 'add-recipe',
  standalone: true,
  imports: [CommonModule, RouterLink],
  templateUrl: './add-recipe.html',
  styleUrl: './add-recipe.css',
})
export class AddRecipe implements OnInit {
  constructor() {}

  ngOnInit(): void {
    const form = document.getElementById('add-recipe-form');
    if (form) {
      form.addEventListener('submit', this.handleSubmit.bind(this));
    }
  }

  handleSubmit(event: Event): void {
    event.preventDefault();

    const name = (document.getElementById('name') as HTMLInputElement).value;
    const author = (document.getElementById('author') as HTMLInputElement).value;
    const type = (document.getElementById('type') as HTMLInputElement).value;
    const instructions = (document.getElementById('instructions') as HTMLTextAreaElement).value;
    const date = (document.getElementById('date') as HTMLInputElement).value;

    if (!name || !author || !type || !instructions || !date) {
      alert('Please fill all fields');
      return;
    }

    const recipe = {
      name,
      author,
      type,
      instructions,
      date
    };

    fetch('http://localhost:8000/API/recipes.php?action=create', {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify(recipe)
    })
    .then(response => response.json())
    .then(data => {
      if (data.success) {
        alert('Recipe added successfully!');
        (document.getElementById('add-recipe-form') as HTMLFormElement).reset();
      } else {
        alert('Error: ' + data.data);
      }
    })
    .catch(error => {
      alert('Error adding recipe. Please try again.');
    });
  }
}
