import { ComponentFixture, TestBed } from '@angular/core/testing';

import { UpdateRecipeInputFormComponent } from './update-recipe-input-form.component';

describe('UpdateRecipeInputFormComponent', () => {
  let component: UpdateRecipeInputFormComponent;
  let fixture: ComponentFixture<UpdateRecipeInputFormComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [UpdateRecipeInputFormComponent]
    })
    .compileComponents();

    fixture = TestBed.createComponent(UpdateRecipeInputFormComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
