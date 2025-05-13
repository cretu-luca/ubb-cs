import { Component, Output, Input, EventEmitter } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';

@Component({
  selector: 'app-filtering-bar',
  standalone: true,
  imports: [CommonModule, FormsModule],
  templateUrl: './filtering-bar.component.html',
  styleUrl: './filtering-bar.component.css'
})
export class FilteringBarComponent {
  @Input() authors: string[] = [];
  @Input() types: string[] = [];
  @Input() lastFilter: string = '';
  
  selectedAuthor: string = '';
  selectedType: string = '';
  
  @Output() authorFilterChange = new EventEmitter<string>();
  @Output() typeFilterChange = new EventEmitter<string>();
  
  onAuthorChange(): void {
    this.authorFilterChange.emit(this.selectedAuthor);
  }
  
  onTypeChange(): void {
    this.typeFilterChange.emit(this.selectedType);
  }
}
