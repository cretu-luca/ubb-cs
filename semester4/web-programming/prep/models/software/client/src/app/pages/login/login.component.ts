import { Component } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';
import { HttpClient, HttpHeaders } from '@angular/common/http';
import { Router } from '@angular/router';

@Component({
  selector: 'app-login',
  standalone: true,
  imports: [CommonModule, FormsModule],
  templateUrl: './login.component.html',
  styleUrl: './login.component.css',
})
export class LoginComponent {
  username: string = '';
  errorMessage: string = '';

  constructor(private http: HttpClient, private router: Router) {}

  login(): void {
    const loginRequest = {
      Username: this.username
    };

    const httpOptions = {
      headers: new HttpHeaders({
        'Content-Type': 'application/json',
      }),
      withCredentials: true,
      observe: 'response' as const,
    };

    this.http
      .post('http://localhost:5262/Auth/Login', loginRequest, httpOptions)
      .subscribe({
        next: (response) => {
          console.log('Login successful:', response);
          this.checkAuthStatus();
        },
        error: (error) => {
          console.error('Login error:', error);
          this.errorMessage = 'Login failed. User not found.';
        },
      });
  }

  checkAuthStatus(): void {
    this.http
      .get('http://localhost:5262/Auth/CheckAuth', {
        withCredentials: true,
      })
      .subscribe({
        next: (response) => {
          console.log('Auth check successful:', response);
          this.router.navigate(['/my-projects']);
        },
        error: (error) => {
          console.error('Auth check error:', error);
          this.errorMessage = 'Authentication failed after login.';
        },
      });
  }
}
