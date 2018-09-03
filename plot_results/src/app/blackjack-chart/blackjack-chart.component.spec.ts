import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { BlackjackChartComponent } from './blackjack-chart.component';

describe('BlackjackChartComponent', () => {
  let component: BlackjackChartComponent;
  let fixture: ComponentFixture<BlackjackChartComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ BlackjackChartComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(BlackjackChartComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
