import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { CommonModule } from '@angular/common';
import { BrowsingTableComponent } from '../../components/browsing-table/browsing-table.component';
import { FilteringBarComponent } from '../../components/filtering-bar/filtering-bar.component';
import { HttpClient, HttpErrorResponse } from '@angular/common/http';

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
  errorMessage: string = '';

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
    this.errorMessage = '';
    
    this.http
      .get<Recipe[]>('https://localhost:7269/Recipe/GetAll', {
        withCredentials: true
      })
      .subscribe({
        next: (data) => {
          if (Array.isArray(data)) {
            this.recipes = data;
            this.extractFilters(data);
          } else {
            this.recipes = [];
          }
        },
        error: (error) => {
          this.recipes = [];
          this.handleError(error);
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
    this.errorMessage = '';

    this.http
      .get<Recipe[]>(
        `https://localhost:7269/Recipe/GetRecipesByAuthor/${author}`,
        { withCredentials: true }
      )
      .subscribe({
        next: (data) => {
          if (Array.isArray(data)) {
            this.recipes = data;
          } else {
            this.recipes = [];
          }
        },
        error: (error) => {
          this.recipes = [];
          this.handleError(error);
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
    this.errorMessage = '';

    this.http
      .get<Recipe[]>(
        `https://localhost:7269/Recipe/GetRecipesByType/${type}`,
        { withCredentials: true }
      )
      .subscribe({
        next: (data) => {
          if (Array.isArray(data)) {
            this.recipes = data;
          } else {
            this.recipes = [];
          }
        },
        error: (error) => {
          this.recipes = [];
          this.handleError(error);
        },
      });
  }

  private handleError(error: HttpErrorResponse): void {
    if (error.status === 401) {
      this.errorMessage = 'You need to be logged in to access this content.';
      this.router.navigate(['/login']);
    } else {
      this.errorMessage = 'An error occurred. Please try again later.';
    }
  }

  private extractFilters(data: Recipe[]): void {
    this.authors = [...new Set(data.map((recipe) => recipe.author))];
    this.types = [...new Set(data.map((recipe) => recipe.type))];
  }
}
