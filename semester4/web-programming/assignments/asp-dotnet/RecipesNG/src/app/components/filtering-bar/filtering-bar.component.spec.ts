import { ComponentFixture, TestBed } from '@angular/core/testing';

import { FilteringBarComponent } from './filtering-bar.component';

describe('FilteringBarComponent', () => {
  let component: FilteringBarComponent;
  let fixture: ComponentFixture<FilteringBarComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [FilteringBarComponent]
    })
    .compileComponents();

    fixture = TestBed.createComponent(FilteringBarComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
