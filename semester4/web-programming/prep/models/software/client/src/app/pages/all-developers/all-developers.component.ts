import { HttpClient } from '@angular/common/http';
import { Component, OnInit } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';

@Component({
  selector: 'app-all-developers',
  standalone: true,
  imports: [CommonModule, FormsModule],
  templateUrl: './all-developers.component.html',
  styleUrl: './all-developers.component.css',
})
export class AllDevelopersComponent implements OnInit {
  developers: any[] = [];
  filteredDevelopers: any[] = [];
  skillFilter: string = '';

  constructor(private http: HttpClient) {}

  ngOnInit() {
    this.loadDevelopers();
  }

  loadDevelopers() {
    this.http
      .get<any[]>('http://localhost:5262/SoftwareDeveloper/GetAll', { withCredentials: true })
      .subscribe((data) => {
        this.developers = data;
        this.filteredDevelopers = data;
      });
  }

  filterDevelopers() {
    if (!this.skillFilter.trim()) {
      this.filteredDevelopers = this.developers;
    } else {
      this.filteredDevelopers = this.developers.filter((developer) =>
        developer.skills.includes(this.skillFilter.trim())
      );
    }
  }
}
