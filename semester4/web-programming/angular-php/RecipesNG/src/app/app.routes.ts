import { Routes } from '@angular/router';
import { AddRecipe } from './pages/AddRecipe/add-recipe';
import { BrowsingComponent } from './pages/Browsing/browsing';
import { DetailsComponent } from './pages/Details/details';

export const routes: Routes = [
  { path: '', redirectTo: '/browse', pathMatch: 'full' },
  { path: 'add-recipe', component: AddRecipe },
  { path: 'browse', component: BrowsingComponent },
  { path: 'details/:id', component: DetailsComponent },
  { path: 'add-ingredient', redirectTo: '/browse' }
];
