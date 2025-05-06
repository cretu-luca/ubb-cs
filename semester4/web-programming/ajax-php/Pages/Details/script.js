$(document).ready(function () {
  const urlParams = new URLSearchParams(window.location.search);
  const recipeId = urlParams.get("id");
  let editMode = false;

  const timestamp = new Date().getTime();

  function loadRecipeData() {
    fetch(`http://localhost:8000/API/recipes.php?action=getByID&id=${recipeId}`)
      .then((response) => response.json())
      .then((data) => {
        if (data.success) {
          const recipe = data.data;
          $("#name").val(recipe.Name);
          $("#author").val(recipe.Author);
          $("#type").val(recipe.Type);
          $("#instructions").val(recipe.Instructions);
          $("#date").val(recipe.Date);

          loadIngredients(recipe.RecipeID);
        }
      })
      .catch((error) => {
        console.error("Failed to fetch recipe details:", error);
      });
  }

  function loadIngredients(recipeId) {
    fetch(
      `http://localhost:8000/API/ingredients.php?action=getIngredientsByRecipeId&recipeId=${recipeId}`
    )
      .then((response) => response.json())
      .then((data) => {
        if (data.success) {
          const ingredients = data.data
            .map(
              (ingredient) =>
                `${ingredient.Name}: ${ingredient.Quantity} ${ingredient.MeasurementUnit}`
            )
            .join("\n");
          $("#ingredients").val(ingredients);
        }
      })
      .catch((error) => {
        console.error("Failed to fetch ingredients:", error);
      });
  }

  loadRecipeData();

  $("#update-button").click(function () {
    if (!editMode) {
      $("#name, #author, #type, #instructions, #date").prop("readonly", false);

      $(this).css("color", "red");
      $(this).text("Save");
      editMode = true;
    } else {
      const updatedRecipe = {
        RecipeID: recipeId,
        Name: $("#name").val(),
        Author: $("#author").val(),
        Type: $("#type").val(),
        Instructions: $("#instructions").val(),
        Date: $("#date").val(),
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
            $("#name, #author, #type, #instructions").prop("readonly", true);

            $("#update-button").css("color", "");
            $("#update-button").text("Update");
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

  $("#delete-button").click(function (e) {
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
            window.location.href = "../Browse";
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

  $("#ingredients-update-button").click(function (e) {
    e.preventDefault();
    window.location.href = `../AddIngredient/index.html?RecipeID=${recipeId}`;
  });

  $("#add-ingredient-button").click(function (e) {
    e.preventDefault();
    window.location.href = `../AddIngredient/index.html?RecipeID=${recipeId}&recipeName=${encodeURIComponent(
      $("#name").val()
    )}`;
  });
});
