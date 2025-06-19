import { Component, OnInit } from "@angular/core";
import { Router } from "@angular/router";
import { CommonModule } from "@angular/common";
import { BrowsingTableComponent } from "../../components/browsing-table/browsing-table.component";
import { FilteringBarComponent } from "../../components/filtering-bar/filtering-bar.component";
import { HttpClient } from "@angular/common/http";

interface Recipe {
  RecipeID: string;
  Name: string;
  Author: string;
  Type: string;
  Instructions: string;
  Date: string;
}

interface ApiResponse {
  success: boolean;
  data: Recipe[] | string;
}

@Component({
  selector: 'browsing',
  standalone: true,
  imports: [CommonModule, BrowsingTableComponent, FilteringBarComponent],
  templateUrl: './browsing.html',
  styleUrl: './browsing.css'
})
export class BrowsingComponent implements OnInit {
  lastFilter: string = '';
  currentFilter: string = '';
  recipes: Recipe[] = [];
  authors: string[] = [];
  types: string[] = [];

  constructor(private router: Router, private http: HttpClient) {}

  ngOnInit(): void {
    this.fetchAllRecipes();
  }

  onTableRowClick(recipeId: string): void {
    if (recipeId) {
      this.router.navigate(['/details', recipeId]);
    }
  }

  fetchAllRecipes(): void {
    this.http.get<ApiResponse>('http://localhost:8000/API/recipes.php?action=all')
      .subscribe({
        next: (result) => {
          if (result.success && Array.isArray(result.data)) {
            this.recipes = result.data; 
            this.extractFilters(result.data);
          } else {
            this.recipes = [];
          }
        },
        error: (_) => {
          this.recipes = [];
        }
      });
  }

  onAuthorChange(author: string): void {
    if (!author) {
      this.fetchAllRecipes();
      return;
    }

    this.lastFilter = this.currentFilter;
    this.currentFilter = author;

    this.http.get<ApiResponse>(`http://localhost:8000/API/recipes.php?action=getByAuthor&author=${author}`)
      .subscribe({
        next: (result) => {
          if (result.success && Array.isArray(result.data)) {
            this.recipes = result.data;
          } else {
            this.recipes = [];
          }
        },
        error: (_) => {
          this.recipes = [];
        }
      });
  }

  onTypeChange(type: string): void {
    if (!type) {
      this.fetchAllRecipes();
      return;
    }

    this.lastFilter = this.currentFilter;
    this.currentFilter = type;

    this.http.get<ApiResponse>(`http://localhost:8000/API/recipes.php?action=getByType&type=${type}`)
      .subscribe({
        next: (result) => {
          if (result.success && Array.isArray(result.data)) {
            this.recipes = result.data;
          } else {
            this.recipes = [];
          }
        },
        error: (_) => {
          this.recipes = [];
        }
      });
  }

  private extractFilters(data: Recipe[]): void {
    this.authors = [...new Set(data.map(recipe => recipe.Author))];
    this.types = [...new Set(data.map(recipe => recipe.Type))];
  }
}