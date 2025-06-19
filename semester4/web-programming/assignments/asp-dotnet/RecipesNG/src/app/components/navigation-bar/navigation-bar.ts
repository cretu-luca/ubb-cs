import { Component, OnInit } from '@angular/core';
import { RouterLink, Router } from '@angular/router';
import { HttpClient } from '@angular/common/http';
import { CommonModule } from '@angular/common';

@Component({
  selector: 'navigation-bar',
  standalone: true,
  imports: [RouterLink, CommonModule],
  templateUrl: './navigation-bar.html',
  styleUrl: './navigation-bar.css'
})
export class NavigationBar implements OnInit {
  isLoggedIn = false;

  constructor(private http: HttpClient, private router: Router) {}

  ngOnInit(): void {
    this.checkAuthStatus();
  }

  checkAuthStatus(): void {
    this.http.get('https://localhost:7269/Auth/CheckAuth', {
      withCredentials: true
    }).subscribe({
      next: () => {
        this.isLoggedIn = true;
      },
      error: () => {
        this.isLoggedIn = false;
      }
    });
  }

  loginOrLogout(): void {
    if (this.isLoggedIn) {
      // If logged in, log out
      this.http.get('https://localhost:7269/Auth/Logout', {
        withCredentials: true
      }).subscribe({
        next: () => {
          this.isLoggedIn = false;
          this.router.navigate(['/login']);
        },
        error: () => {
          // Even on error, try to navigate to login
          this.isLoggedIn = false;
          this.router.navigate(['/login']);
        }
      });
    } else {
      // If not logged in, go to login page
      this.router.navigate(['/login']);
    }
  }
}