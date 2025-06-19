import { Routes } from '@angular/router';
import { AddRecipe } from './pages/add-recipe/add-recipe';
import { BrowsingComponent } from './pages/Browsing/browsing';
import { DetailsComponent } from './pages/Details/details';
import { LoginComponent } from './pages/login/login';

export const routes: Routes = [
  { path: '', redirectTo: '/login', pathMatch: 'full' },
  { path: 'login', component: LoginComponent },
  { path: 'add-recipe', component: AddRecipe },
  { path: 'browse', component: BrowsingComponent },
  { path: 'details/:id', component: DetailsComponent },
  { path: 'add-ingredient', redirectTo: '/browse' }
];
