$(document).ready(function () {
  const urlParams = new URLSearchParams(window.location.search);
  const recipeId = urlParams.get("RecipeID");

  $('#add-ingredient-form').on('submit', function(e) {
    e.preventDefault();
    return false;
  });

  window.addIngredient = function(event) {
    event.preventDefault();
    
    const name = $('#name').val();
    const quantity = $('#quantity').val();
    const measurementUnit = $('#measurementUnit').val();
    
    if (!name || !quantity || !measurementUnit) {
      alert('Please fill all fields');
      return;
    }

    const ingredient = {
      Name: name,
      Quantity: parseInt(quantity),
      MeasurementUnit: measurementUnit,
      RecipeID: parseInt(recipeId)
    };

    fetch('http://localhost:8000/API/ingredients.php?action=create', {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json'
      },
      body: JSON.stringify(ingredient)
    })
    .then(response => response.json())
    .then(data => {
      if (data.success) {
        alert('Ingredient added successfully!');
        // window.location.href = `../Details/index.html?name=${encodeURIComponent(urlParams.get('recipeName') || '')}`;
        window.location.replace(`../Browse/index.html`);
      } else {
        alert('Failed to add ingredient: ' + (data.data || 'Unknown error'));
      }
    })
    .catch(error => {
      alert('Error adding ingredient: ' + error);
    });
  };
});
