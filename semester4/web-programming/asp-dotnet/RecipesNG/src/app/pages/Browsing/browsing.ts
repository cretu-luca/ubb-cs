import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { CommonModule } from '@angular/common';
import { BrowsingTableComponent } from '../../components/browsing-table/browsing-table.component';
import { FilteringBarComponent } from '../../components/filtering-bar/filtering-bar.component';
import { HttpClient } from '@angular/common/http';

interface ApiResponse {
  success: boolean;
  data: any;
}

interface Recipe {
  recipeID: string;
  name: string;
  author: string;
  type: string;
  instructions: string;
  date: string;
}

@Component({
  selector: 'browsing',
  standalone: true,
  imports: [CommonModule, BrowsingTableComponent, FilteringBarComponent],
  templateUrl: './browsing.html',
  styleUrl: './browsing.css',
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
    this.http
      .get<Recipe[]>('https://localhost:7269/Recipe/GetAll')
      .subscribe({
        next: (data) => {
          if (Array.isArray(data)) {
            this.recipes = data;
            this.extractFilters(data);
          } else {
            this.recipes = [];
          }
        },
        error: (_) => {
          this.recipes = [];
        },
      });
  }

  onAuthorChange(author: string): void {
    if (!author) {
      this.fetchAllRecipes();
      return;
    }

    this.lastFilter = this.currentFilter;
    this.currentFilter = author;

    this.http
      .get<Recipe[]>(
        `https://localhost:7269/Recipe/GetRecipesByAuthor/${author}`
      )
      .subscribe({
        next: (data) => {
          if (Array.isArray(data)) {
            this.recipes = data;
          } else {
            this.recipes = [];
          }
        },
        error: (_) => {
          this.recipes = [];
        },
      });
  }

  onTypeChange(type: string): void {
    if (!type) {
      this.fetchAllRecipes();
      return;
    }

    this.lastFilter = this.currentFilter;
    this.currentFilter = type;

    this.http
      .get<Recipe[]>(
        `https://localhost:7269/Recipe/GetRecipesByType/${type}`
      )
      .subscribe({
        next: (data) => {
          if (Array.isArray(data)) {
            this.recipes = data;
          } else {
            this.recipes = [];
          }
        },
        error: (_) => {
          this.recipes = [];
        },
      });
  }

  private extractFilters(data: Recipe[]): void {
    this.authors = [...new Set(data.map((recipe) => recipe.author))];
    this.types = [...new Set(data.map((recipe) => recipe.type))];
  }
}
