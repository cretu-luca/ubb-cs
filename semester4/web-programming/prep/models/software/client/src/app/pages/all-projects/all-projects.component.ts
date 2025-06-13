import { HttpClient } from '@angular/common/http';
import { Component } from '@angular/core';
import { OnInit } from '@angular/core';
import { CommonModule } from '@angular/common';

@Component({
  selector: 'app-all-projects',
  imports: [CommonModule],
  templateUrl: './all-projects.component.html',
  styleUrl: './all-projects.component.css',
})
export class AllProjectsComponent implements OnInit {
  projects: any[] = [];

  constructor(private http: HttpClient) {}

  ngOnInit() {
    this.http
      .get<any[]>('http://localhost:5262/Project/GetAll', { withCredentials: true })
      .subscribe((data) => (this.projects = data));
  }
}
