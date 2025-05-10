import { Component, OnInit } from '@angular/core';
import { ActivatedRoute, Router } from '@angular/router';
import { CommonModule } from '@angular/common';

@Component({
  selector: 'recipe-details',
  standalone: true,
  imports: [CommonModule],
  templateUrl: './details.html',
  styleUrl: './details.css'
})
export class DetailsComponent implements OnInit {
  constructor(private route: ActivatedRoute, private router: Router) {}

  ngOnInit(): void {
    let recipeId = '';
    let editMode = false;

    this.route.paramMap.subscribe(params => {
      recipeId = params.get('id') || '';
    });

    function loadRecipeData() {
      fetch(`http://localhost:8000/API/recipes.php?action=getByID&id=${recipeId}`)
        .then((response) => response.json())
        .then((data) => {
          if (data.success) {
            const recipe = data.data;
            document.getElementById('name')!.setAttribute('value', recipe.Name);
            document.getElementById('author')!.setAttribute('value', recipe.Author);
            document.getElementById('type')!.setAttribute('value', recipe.Type);
            (document.getElementById('instructions') as HTMLTextAreaElement).value = recipe.Instructions;
            document.getElementById('date')!.setAttribute('value', recipe.Date);

            loadIngredients(recipe.RecipeID);
          }
        })
        .catch((error) => {
          console.error("Failed to fetch recipe details:", error);
        });
    }

    function loadIngredients(recipeId: string) {
      fetch(
        `http://localhost:8000/API/ingredients.php?action=getIngredientsByRecipeId&recipeId=${recipeId}`
      )
        .then((response) => response.json())
        .then((data) => {
          if (data.success) {
            const ingredients = data.data
              .map(
                (ingredient: any) =>
                  `${ingredient.Name}: ${ingredient.Quantity} ${ingredient.MeasurementUnit}`
              )
              .join("\n");
            (document.getElementById('ingredients') as HTMLTextAreaElement).value = ingredients;
          }
        })
        .catch((error) => {
          console.error("Failed to fetch ingredients:", error);
        });
    }

    loadRecipeData();

    setTimeout(() => {
      const updateButton = document.getElementById('update-button');
      if (updateButton) {
        updateButton.addEventListener('click', function() {
          if (!editMode) {
            const formElements = document.querySelectorAll('#name, #author, #type, #instructions, #date');
            formElements.forEach(element => {
              element.removeAttribute('readonly');
            });

            this.style.color = 'red';
            this.textContent = 'Save';
            editMode = true;
          } else {
            const updatedRecipe = {
              RecipeID: recipeId,
              Name: (document.getElementById('name') as HTMLInputElement).value,
              Author: (document.getElementById('author') as HTMLInputElement).value,
              Type: (document.getElementById('type') as HTMLInputElement).value,
              Instructions: (document.getElementById('instructions') as HTMLTextAreaElement).value,
              Date: (document.getElementById('date') as HTMLInputElement).value,
            };

            fetch("http://localhost:8000/API/recipes.php?action=update", {
              method: "PUT",
              headers: {
                "Content-Type": "application/json",
              },
              body: JSON.stringify(updatedRecipe),
            })
              .then((response) => response.json())
              .then((data) => {
                if (data.success) {
                  alert("Recipe updated successfully!");
                  
                  const formElements = document.querySelectorAll('#name, #author, #type, #instructions, #date');
                  formElements.forEach(element => {
                    element.setAttribute('readonly', 'true');
                  });

                  this.style.color = '';
                  this.textContent = 'Update';
                  editMode = false;
                } else {
                  alert("Failed to update recipe: " + (data.data || "Unknown error"));
                }
              })
              .catch((error) => {
                console.error("Error updating recipe:", error);
                alert("Error updating recipe: " + error);
              });
          }
        });
      }

      const deleteButton = document.getElementById('delete-button');
      if (deleteButton) {
        deleteButton.addEventListener('click', (e) => {
          e.preventDefault();

          if (confirm("Are you sure you want to delete this recipe?")) {
            fetch(
              `http://localhost:8000/API/recipes.php?action=delete&id=${recipeId}`,
              {
                method: "DELETE",
              }
            )
              .then((response) => response.json())
              .then((data) => {
                if (data.success) {
                  alert("Recipe deleted successfully!");
                  this.router.navigate(['/browse']);
                } else {
                  alert("Failed to delete recipe: " + (data.data || "Unknown error"));
                }
              })
              .catch((error) => {
                console.error("Error deleting recipe:", error);
                alert("Error deleting recipe: " + error);
              });
          }
        });
      }

      const ingredientsUpdateButton = document.getElementById('ingredients-update-button');
      if (ingredientsUpdateButton) {
        ingredientsUpdateButton.addEventListener('click', (e) => {
          e.preventDefault();
          this.router.navigate(['/add-ingredient'], { 
            queryParams: { RecipeID: recipeId }
          });
        });
      }

      const addIngredientButton = document.getElementById('add-ingredient-button');
      if (addIngredientButton) {
        addIngredientButton.addEventListener('click', (e) => {
          e.preventDefault();
          const recipeName = (document.getElementById('name') as HTMLInputElement).value;
          this.router.navigate(['/add-ingredient'], { 
            queryParams: { 
              RecipeID: recipeId,
              recipeName: recipeName
            }
          });
        });
      }
    }, 100);
  }
} 