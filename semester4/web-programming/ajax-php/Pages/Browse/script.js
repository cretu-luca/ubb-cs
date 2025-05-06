$(document).ready(function () {
  var lastFilter = "";
  const lastFilterInput = $("#history-input");

  fetch("http://localhost:8000/API/recipes.php?action=all")
    .then((response) => response.json())
    .then((result) => {
      if (result.success) {
        createTable(result.data);
        loadFilterFields(result.data);
      } else {
        $("#browsing-table").html("<tr><td>Error loading recipes</td></tr>");
      }
    });

  $("#filter-by-author").on("change", function () {
    const author = $(this).val();

    if (!author) {
      fetch("http://localhost:8000/API/recipes.php?action=all")
        .then((response) => response.json())
        .then((result) => {
          if (result.success) {
            createTable(result.data);
          } else {
            $("#browsing-table").html(
              "<tr><td>Error loading recipes</td></tr>"
            );
          }
        })
        .catch((error) => {
          console.error("Error:", error);
          $("#browsing-table").html("<tr><td>Error loading recipes</td></tr>");
        });
      return;
    }

    lastFilterInput.val(lastFilter);
    lastFilter = author;

    fetch(
      `http://localhost:8000/API/recipes.php?action=getByAuthor&author=${author}`
    )
      .then((response) => response.json())
      .then((result) => {
        if (result.success) {
          createTable(result.data);
        } else {
          $("#browsing-table").html(
            "<tr><td>Error: " + (result.data || "Unknown error") + "</td></tr>"
          );
        }
      })
      .catch((error) => {
        $("#browsing-table").html("<tr><td>Error loading recipes</td></tr>");
      });
  });

  $("#filter-by-type").on("change", function () {
    const type = $(this).val();

    if (!type) {
      fetch("http://localhost:8000/API/recipes.php?action=all")
        .then((response) => response.json())
        .then((result) => {
          if (result.success) {
            createTable(result.data);
          } else {
            $("#browsing-table").html(
              "<tr><td>Error loading recipes</td></tr>"
            );
          }
        })
        .catch((error) => {
          $("#browsing-table").html("<tr><td>Error loading recipes</td></tr>");
        });
      return;
    }

    lastFilterInput.val(lastFilter);
    lastFilter = type;

    fetch(`http://localhost:8000/API/recipes.php?action=getByType&type=${type}`)
      .then((response) => response.json())
      .then((result) => {
        if (result.success) {
          createTable(result.data);
        } else {
          $("#browsing-table").html(
            "<tr><td>Error: " + (result.data || "Unknown error") + "</td></tr>"
          );
        }
      })
      .catch((error) => {
        $("#browsing-table").html("<tr><td>Error loading recipes</td></tr>");
      });
  });

  $("#browsing-table").on("click", "tr", function () {
    const recipeID = $(this).find("td.recipe-id").text();
    if (recipeID) {
      window.location.href = `../Details/index.html?id=${recipeID}`;
    }
  });

  function createTable(data) {
    const $table = $("#browsing-table");
    $table.empty();

    $table.append(
      "<tr><th>Name</th><th>Author</th><th>Type</th><th>Instructions</th><th>Date</th></tr>"
    );

    if (!data || data.length === 0) {
      $table.append("<tr><td colspan='5'>No recipes found</td></tr>");
      return;
    }

    data.forEach((recipe) => {
      $table.append(
        `<tr>
          <td class="recipe-id">${recipe.RecipeID}</td>
          <td>${recipe.Name}</td>
          <td>${recipe.Author}</td>
          <td>${recipe.Type}</td>
          <td>${recipe.Instructions}</td>
          <td>${recipe.Date}</td>
        </tr>`
      );
    });
  }

  function loadFilterFields(data) {
    const $filterByAuthorSelect = $("#filter-by-author");
    const $filterByTypeSelect = $("#filter-by-type");

    $filterByAuthorSelect.empty();
    $filterByTypeSelect.empty();

    $filterByAuthorSelect.append(
      $("<option>", {
        value: "",
        text: "All Authors",
      })
    );

    $filterByTypeSelect.append(
      $("<option>", {
        value: "",
        text: "All Types",
      })
    );

    const authors = [];
    data.forEach((recipe) => {
      if (!authors.includes(recipe.Author)) {
        authors.push(recipe.Author);
      }
    });

    authors.forEach((author) => {
      $filterByAuthorSelect.append(
        $("<option>", {
          value: author,
          text: author,
        })
      );
    });
    const types = [];
    data.forEach((recipe) => {
      if (!types.includes(recipe.Type)) {
        types.push(recipe.Type);
      }
    });

    types.forEach((type) => {
      $filterByTypeSelect.append(
        $("<option>", {
          value: type,
          text: type,
        })
      );
    });
  }
});
