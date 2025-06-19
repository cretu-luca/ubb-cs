import { Component } from '@angular/core';
import { RouterOutlet, RouterLink } from '@angular/router';
import { NavigationBar } from './components/navigation-bar/navigation-bar';

@Component({
  selector: 'app-root',
  standalone: true, 
  imports: [RouterOutlet, RouterLink, NavigationBar],
  templateUrl: './app.component.html',
  styleUrl: './app.component.css'
})
export class AppComponent {
  title = 'salut';
}
