import { Routes } from '@angular/router';
import { LoginComponent } from './pages/login/login.component';
import { AllProjectsComponent } from './pages/all-projects/all-projects.component';
import { MyProjectsComponent } from './pages/my-projects/my-projects.component';
import { AssignComponent } from './pages/assign/assign.component';
import { AllDevelopersComponent } from './pages/all-developers/all-developers.component';

export const routes: Routes = [
  { path: 'login', component: LoginComponent },
  { path: 'all-projects', component: AllProjectsComponent },
  { path: 'my-projects', component: MyProjectsComponent },
  { path: 'assign', component: AssignComponent },
  { path: 'all-developers', component: AllDevelopersComponent },
];
