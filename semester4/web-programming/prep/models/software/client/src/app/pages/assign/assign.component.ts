import { Component } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';
import { HttpClient } from '@angular/common/http';

@Component({
  selector: 'app-assign',
  standalone: true,
  imports: [CommonModule, FormsModule],
  templateUrl: './assign.component.html',
  styleUrl: './assign.component.css',
})
export class AssignComponent {
  userid: string = '';
  projectNames: string = '';

  constructor(private http: HttpClient) {}

  handleAssign() {
    this.http.post('http://localhost:5262/Project/Assign', 
      { userid: this.userid, projectNames: this.projectNames },
      { withCredentials: true })
      .subscribe(response => console.log(response));
  }
}
