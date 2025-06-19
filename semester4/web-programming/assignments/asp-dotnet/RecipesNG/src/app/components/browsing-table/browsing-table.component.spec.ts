import { ComponentFixture, TestBed } from '@angular/core/testing';

import { BrowsingTableComponent } from './browsing-table.component';

describe('BrowsingTableComponent', () => {
  let component: BrowsingTableComponent;
  let fixture: ComponentFixture<BrowsingTableComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [BrowsingTableComponent]
    })
    .compileComponents();

    fixture = TestBed.createComponent(BrowsingTableComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
