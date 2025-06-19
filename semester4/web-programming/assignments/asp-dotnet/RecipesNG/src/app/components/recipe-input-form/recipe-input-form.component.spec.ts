import { ComponentFixture, TestBed } from '@angular/core/testing';

import { RecipeInputFormComponent } from './recipe-input-form.component';

describe('RecipeInputFormComponent', () => {
  let component: RecipeInputFormComponent;
  let fixture: ComponentFixture<RecipeInputFormComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [RecipeInputFormComponent]
    })
    .compileComponents();

    fixture = TestBed.createComponent(RecipeInputFormComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
