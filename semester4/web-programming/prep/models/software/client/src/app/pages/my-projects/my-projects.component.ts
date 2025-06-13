import { Component } from '@angular/core';
import { OnInit } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { CommonModule } from '@angular/common';

@Component({
  selector: 'app-my-projects',
  standalone: true,
  imports: [CommonModule],
  templateUrl: './my-projects.component.html',
  styleUrl: './my-projects.component.css',
})
export class MyProjectsComponent implements OnInit {
  projects: any[] = [];
  currentUserId: string = '';
  currentUsername: string = '';

  constructor(private http: HttpClient) {}

  ngOnInit() {
    this.http.get<any>('http://localhost:5262/Auth/CheckAuth', { withCredentials: true })
      .subscribe({
        next: (authData) => {
          if (authData.isAuthenticated) {
            this.currentUserId = authData.userId;
            this.currentUsername = authData.username;
            
            this.loadUserProjects();
          }
        },
        error: (error) => {
          console.log('User not authenticated', error);
        }
      });
  }

  loadUserProjects() {
    this.http.get<any[]>('http://localhost:5262/Project/GetAll', { withCredentials: true })
      .subscribe((data) => {
        this.projects = data.filter(project =>  
          project.members && project.members.includes(this.currentUserId)
        );
      });
  }
}
