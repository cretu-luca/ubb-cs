import {
  Component,
  Output,
  EventEmitter,
  Input,
  OnChanges,
  SimpleChanges,
} from '@angular/core';
import { CommonModule } from '@angular/common';
import { ViewChild, ElementRef, AfterViewInit } from '@angular/core';

interface Recipe {
  recipeID: string;
  name: string;
  author: string;
  type: string;
  instructions: string;
  date: string;
}

@Component({
  selector: 'app-browsing-table',
  standalone: true,
  imports: [CommonModule],
  templateUrl: './browsing-table.component.html',
  styleUrl: './browsing-table.component.css',
})
export class BrowsingTableComponent implements OnChanges, AfterViewInit {
  @Input() recipes: Recipe[] = [];
  @Input() numberOfElements: string = '';
  @Output() onRowClick = new EventEmitter<string>();
  @ViewChild('browsingTable') tableRef!: ElementRef<HTMLTableElement>;

  ngAfterViewInit() {
    this.updateTable();
  }

  ngOnChanges(changes: SimpleChanges): void {
    if (changes['recipes'] && this.tableRef) {
      this.updateTable();
    }
  }

  handleRowClick(recipeId: string): void {
    this.onRowClick.emit(recipeId);
  }

  updateTable(): void {
    const table = this.tableRef.nativeElement;
    this.numberOfElements = String(this.recipes.length);

    while (table.rows.length > 1) {
      table.deleteRow(1);
    }

    this.recipes.forEach((recipe) => {
      const row = table.insertRow();
      row.onclick = () => this.handleRowClick(recipe.recipeID);

      const nameCell = row.insertCell();
      nameCell.textContent = recipe.name;

      const authorCell = row.insertCell();
      authorCell.textContent = recipe.author;

      const typeCell = row.insertCell();
      typeCell.textContent = recipe.type;

      const instructionsCell = row.insertCell();
      instructionsCell.textContent = recipe.instructions;

      const dateCell = row.insertCell();
      dateCell.textContent = recipe.date;
    });
  }
}
