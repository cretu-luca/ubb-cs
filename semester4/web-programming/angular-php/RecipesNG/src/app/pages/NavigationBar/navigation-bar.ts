import { Component } from '@angular/core';
import { RouterLink } from '@angular/router';

@Component({
  selector: 'navigation-bar',
  standalone: true,
  imports: [RouterLink],
  templateUrl: './navigation-bar.html',
  styleUrl: './navigation-bar.css'
})
export class NavigationBar {
  constructor() {}
}