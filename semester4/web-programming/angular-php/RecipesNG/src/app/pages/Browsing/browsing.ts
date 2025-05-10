import { Component, OnInit } from "@angular/core";
import { Router } from "@angular/router";
import { CommonModule } from "@angular/common";

interface Recipe {
  RecipeID: string;
  Name: string;
  Author: string;
  Type: string;
  Instructions: string;
  Date: string;
}

@Component({
  selector: 'browsing',
  standalone: true,
  imports: [CommonModule],
  templateUrl: './browsing.html',
  styleUrl: './browsing.css'
})
export class BrowsingComponent implements OnInit {
  lastFilter: string = '';

  constructor(private router: Router) {}

  ngOnInit(): void {
    this.fetchAllRecipes();
    this.setupEventListeners();
  }

  setupEventListeners(): void {
    const authorSelect = document.getElementById('filter-by-author') as HTMLSelectElement;
    if (authorSelect) {
      authorSelect.addEventListener('change', () => {
        this.onAuthorChange(authorSelect.value);
      });
    }

    const typeSelect = document.getElementById('filter-by-type') as HTMLSelectElement;
    if (typeSelect) {
      typeSelect.addEventListener('change', () => {
        this.onTypeChange(typeSelect.value);
      });
    }

    const table = document.getElementById('browsing-table');
    if (table) {
      table.addEventListener('click', (event) => {
        const target = event.target as HTMLElement;
        const row = target.closest('tr');
        if (row) {
          const recipeIdCell = row.querySelector('.recipe-id');
          if (recipeIdCell) {
            this.onTableRowClick(recipeIdCell.textContent || '');
          }
        }
      });
    }
  }

  fetchAllRecipes(): void {
    fetch('http://localhost:8000/API/recipes.php?action=all')
      .then(response => response.json())
      .then(result => {
        if (result.success) {
          this.createTable(result.data);
          this.loadFilterFields(result.data);
        } else {
          const table = document.getElementById('browsing-table');
          if (table) {
            table.innerHTML = "<tr><td>Error loading recipes</td></tr>";
          }
        }
      })
      .catch(error => {
        console.error("Error:", error);
        const table = document.getElementById('browsing-table');
        if (table) {
          table.innerHTML = "<tr><td>Error loading recipes</td></tr>";
        }
      });
  }

  onAuthorChange(author: string): void {
    if (!author) {
      this.fetchAllRecipes();
      return;
    }

    const historyInput = document.getElementById('history-input') as HTMLInputElement;
    if (historyInput) {
      historyInput.value = this.lastFilter;
    }
    this.lastFilter = author;

    fetch(`http://localhost:8000/API/recipes.php?action=getByAuthor&author=${author}`)
      .then(response => response.json())
      .then(result => {
        if (result.success) {
          this.createTable(result.data);
        } else {
          const table = document.getElementById('browsing-table');
          if (table) {
            table.innerHTML = "<tr><td>Error: " + (result.data || "Unknown error") + "</td></tr>";
          }
        }
      })
      .catch(error => {
        const table = document.getElementById('browsing-table');
        if (table) {
          table.innerHTML = "<tr><td>Error loading recipes</td></tr>";
        }
      });
  }

  onTypeChange(type: string): void {
    if (!type) {
      this.fetchAllRecipes();
      return;
    }

    const historyInput = document.getElementById('history-input') as HTMLInputElement;
    if (historyInput) {
      historyInput.value = this.lastFilter;
    }
    this.lastFilter = type;

    
    fetch(`http://localhost:8000/API/recipes.php?action=getByType&type=${type}`)
      .then(response => response.json())
      .then(result => {
        if (result.success) {
          this.createTable(result.data);
        } else {
          const table = document.getElementById('browsing-table');
          if (table) {
            table.innerHTML = "<tr><td>Error: " + (result.data || "Unknown error") + "</td></tr>";
          }
        }
      })
      .catch(error => {
        const table = document.getElementById('browsing-table');
        if (table) {
          table.innerHTML = "<tr><td>Error loading recipes</td></tr>";
        }
      });
  }

  onTableRowClick(recipeId: string): void {
    if (recipeId) {
      this.router.navigate(['/details', recipeId]);
    }
  }

  private createTable(data: Recipe[]): void {
    const table = document.getElementById('browsing-table');
    if (!table) return;

    table.innerHTML = '';

    const headerRow = document.createElement('tr');
    headerRow.innerHTML = "<th>Name</th><th>Author</th><th>Type</th><th>Instructions</th><th>Date</th>";
    table.appendChild(headerRow);

    if (!data || data.length === 0) {
      const noDataRow = document.createElement('tr');
      noDataRow.innerHTML = "<td colspan='5'>No recipes found</td>";
      table.appendChild(noDataRow);
      return;
    }

    data.forEach(recipe => {
      const row = document.createElement('tr');
      row.innerHTML = `
        <td class="recipe-id" style="display:none;">${recipe.RecipeID}</td>
        <td>${recipe.Name}</td>
        <td>${recipe.Author}</td>
        <td>${recipe.Type}</td>
        <td>${recipe.Instructions}</td>
        <td>${recipe.Date}</td>
      `;
      table.appendChild(row);
    });
  }

  private loadFilterFields(data: Recipe[]): void {
    const authorSelect = document.getElementById('filter-by-author') as HTMLSelectElement;
    const typeSelect = document.getElementById('filter-by-type') as HTMLSelectElement;
    
    if (!authorSelect || !typeSelect) return;

    authorSelect.innerHTML = '';
    typeSelect.innerHTML = '';

    const defaultAuthorOption = document.createElement('option');
    defaultAuthorOption.value = '';
    defaultAuthorOption.text = 'All Authors';
    authorSelect.appendChild(defaultAuthorOption);

    const defaultTypeOption = document.createElement('option');
    defaultTypeOption.value = '';
    defaultTypeOption.text = 'All Types';
    typeSelect.appendChild(defaultTypeOption);

    const authors: string[] = [];
    data.forEach((recipe) => {
      if (!authors.includes(recipe.Author)) {
        authors.push(recipe.Author);
      }
    });

    authors.forEach(author => {
      const option = document.createElement('option');
      option.value = author;
      option.text = author;
      authorSelect.appendChild(option);
    });

    const types: string[] = [];
    data.forEach((recipe) => {
      if (!types.includes(recipe.Type)) {
        types.push(recipe.Type);
      }
    });

    types.forEach(type => {
      const option = document.createElement('option');
      option.value = type;
      option.text = type;
      typeSelect.appendChild(option);
    });
  }
}