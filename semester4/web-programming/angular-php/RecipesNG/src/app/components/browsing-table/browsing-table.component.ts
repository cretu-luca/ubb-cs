import { Component, Output, EventEmitter, Input, OnChanges, SimpleChanges } from '@angular/core';
import { CommonModule } from '@angular/common';
import { ViewChild, ElementRef, AfterViewInit } from '@angular/core';

interface Recipe {
  RecipeID: string;
  Name: string;
  Author: string;
  Type: string;
  Instructions: string;
  Date: string;
}

@Component({
  selector: 'app-browsing-table',
  standalone: true,
  imports: [CommonModule],
  templateUrl: './browsing-table.component.html',
  styleUrl: './browsing-table.component.css'
})
export class BrowsingTableComponent implements OnChanges, AfterViewInit {
  @Input() recipes: Recipe[] = [];
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
    
    while (table.rows.length > 1) {
      table.deleteRow(1);
    }
    
    this.recipes.forEach(recipe => {
      const row = table.insertRow();
      row.onclick = () => this.handleRowClick(recipe.RecipeID);
      
      const nameCell = row.insertCell();
      nameCell.textContent = recipe.Name;
      
      const authorCell = row.insertCell();
      authorCell.textContent = recipe.Author;
      
      const typeCell = row.insertCell();
      typeCell.textContent = recipe.Type;
      
      const instructionsCell = row.insertCell();
      instructionsCell.textContent = recipe.Instructions;
      
      const dateCell = row.insertCell();
      dateCell.textContent = recipe.Date;
    });
  }
}
