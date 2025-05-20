import { Component } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';
import { Router } from '@angular/router';
import { HttpClient, HttpHeaders } from '@angular/common/http';

@Component({
  selector: 'app-login',
  standalone: true,
  imports: [CommonModule, FormsModule],
  templateUrl: './login.html',
  styleUrl: './login.css'
})
export class LoginComponent {
  username: string = '';
  password: string = '';
  errorMessage: string = '';

  constructor(private http: HttpClient, private router: Router) {}

  login(): void {
    if (!this.username || !this.password) {
      this.errorMessage = 'Please enter both username and password';
      return;
    }

    const credentials = {
      username: this.username,
      password: this.password
    };

    const httpOptions = {
      headers: new HttpHeaders({
        'Content-Type': 'application/json'
      }),
      withCredentials: true,
      observe: 'response' as const
    };

    this.http.post('https://localhost:7269/Auth/Login', credentials, httpOptions)
      .subscribe({
        next: (response) => {
          this.checkAuthStatus();
        },
        error: (error) => {
          this.errorMessage = 'Login failed. Please check your credentials.';
        }
      });
  }

  checkAuthStatus(): void {
    this.http.get('https://localhost:7269/Auth/CheckAuth', {
      withCredentials: true
    }).subscribe({
      next: (response) => {
        this.router.navigate(['/browse']);
      },
      error: (error) => {
        this.errorMessage = 'Authentication failed after login.';
      }
    });
  }
} 