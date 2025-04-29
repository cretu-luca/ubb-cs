$(document).ready(function() {
    const urlParams = new URLSearchParams(window.location.search);
    const recipeName = urlParams.get('name');
    let recipeId;
    let editMode = false;

    fetch(`http://localhost:8000/API/recipes.php?action=getByName&name=${recipeName}`)
        .then(response => response.json())
        .then(data => {
            if (data.success) {
                const recipe = data.data;
                recipeId = recipe.RecipeID;
                $('#name').val(recipe.Name);
                $('#author').val(recipe.Author);
                $('#type').val(recipe.Type);
                $('#instructions').val(recipe.Instructions);
                fetch(`http://localhost:8000/API/ingredients.php?action=getIngredientsByRecipeId&recipeId=${recipe.RecipeID}`)
                    .then(response => response.json())
                    .then(data => {
                        if (data.success) {
                            const ingredients = data.data.map(ingredient => 
                                `${ingredient.Name}: ${ingredient.Quantity} ${ingredient.MeasurementUnit}`
                            ).join('\n');
                            $('#ingredients').val(ingredients);
                        }
                    })
                    .catch(error => {
                        console.error('Failed to fetch ingredients:', error);
                    });
            }
        })
        .catch(error => {
            console.error('Failed to fetch recipe details:', error);
        });

    



    // check below








    $('#update-button').click(function() {
        if (!editMode) {
            // Enter edit mode
            $('#name, #author, #type, #instructions, #ingredients').prop('readonly', false);
            $(this).css('color', 'red');
            $(this).text('Save');
            editMode = true;
        } else {
            // Save changes
            const updatedRecipe = {
                RecipeID: recipeId,
                Name: $('#name').val(),
                Author: $('#author').val(),
                Type: $('#type').val(),
                Instructions: $('#instructions').val()
            };

            fetch('http://localhost:8000/API/recipes.php?action=update', {
                method: 'PUT',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify(updatedRecipe)
            })
            .then(response => response.json())
            .then(data => {
                if (data.success) {
                    alert('Recipe updated successfully!');
                    $('#name, #author, #type, #instructions, #ingredients').prop('readonly', true);
                    $('#update-button').css('color', '');
                    $('#update-button').text('Update');
                    editMode = false;
                } else {
                    alert('Failed to update recipe: ' + (data.data || 'Unknown error'));
                }
            })
            .catch(error => {
                console.error('Error updating recipe:', error);
                alert('Error updating recipe: ' + error);
            });
        }
    });

    $('#delete-button').click(function() {
        if (confirm('Are you sure you want to delete this recipe?')) {
            fetch(`http://localhost:8000/API/recipes.php?action=delete&id=${recipeId}`, {
                method: 'DELETE'
            })
            .then(response => response.json())
            .then(data => {
                if (data.success) {
                    alert('Recipe deleted successfully!');
                    window.location.href = '../Browse';
                } else {
                    alert('Failed to delete recipe: ' + (data.data || 'Unknown error'));
                }
            })
            .catch(error => {
                console.error('Error deleting recipe:', error);
                alert('Error deleting recipe: ' + error);
            });
        }
    });
});
