import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';

import { AppComponent } from './app.component';
import { BlackjackChartComponent } from './blackjack-chart/blackjack-chart.component';

@NgModule({
  declarations: [
    AppComponent,
    BlackjackChartComponent
  ],
  imports: [
    BrowserModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
