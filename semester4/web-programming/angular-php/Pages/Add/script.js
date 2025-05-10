function addRecipe(event) {
  if (event) event.preventDefault();

  const name = document.getElementById("name").value;
  const author = document.getElementById("author").value;
  const type = document.getElementById("type").value;
  const instructions = document.getElementById("instructions").value;
  const date = document.getElementById("date-created").value;

  if (!name || !author || !type || !instructions || !date) {
    alert("Please fill all fields");
    return;
  }

  fetch("http://localhost:8000/API/recipes.php?action=create", {
    method: "POST",
    body: JSON.stringify({ name, author, type, instructions, date }),
    headers: {
      "Content-Type": "application/json",
    },
  })
    .then((response) => response.json())
    .then((data) => {
      console.log("Success:", data);
      if (data.success) {
        alert("Recipe added successfully!");
        document.getElementById("add-recipe-form").reset();
      } else {
        alert("Error: " + data.data);
      }
    })
    .catch((error) => {
      alert("Error adding recipe. Please try again.");
    });
}
