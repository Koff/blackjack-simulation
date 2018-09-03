import {Component, OnInit} from '@angular/core';
import * as d3 from "d3";
import * as d3_color from "d3-color";
import * as d3_legend from "d3-svg-legend";

@Component({
  selector: 'app-blackjack-chart',
  templateUrl: './blackjack-chart.component.html',
  styleUrls: ['./blackjack-chart.component.css']
})
export class BlackjackChartComponent implements OnInit {

  ngOnInit() {
    var square_width = 26;
    var square_height = 26;

    function create_heatmap(level, starts_with) {
      var filename = '/assets/blackjack-' + level + '-cards-hands.txt';
      var div = d3.select('body')
      .append('div')
      .style("opacity", 0)
      .style("position", "absolute")
      .style("background", "lightblue")
      .style("width", "80px")
      .style("height", "30px")
      .style("padding", "2px");

      d3.csv(filename).then(function (csv) {
        var calculated_width = function (level) {
          if (level == 2)
          {
            return 54;
          }
          else
          {
            return 10;
          }
        };
        var heat_map = d3.select('body')
          .append("div")
          .attr("id", 'level-' + level)
          .append("svg")
          .attr("width", calculated_width * square_width )
          .attr("height", square_height * 11)
          .attr("preserveAspectRatio", "xMinYMin meet")
          .attr("viewBox", "0 0 1404 286")
          .style("background-color", "#303030")
          .append('g')
          .selectAll('rect')
          .data(csv)
          .enter()
          .filter(function(d) { return d.player_hand.startsWith(starts_with) })
          .append('rect')
          .attr('x', function(d, i) { return Math.trunc(i/10) * square_width + square_width })
          .attr('y', function(d, i) { return i % 10 * square_height + square_height; })
          .attr('width', square_width)
          .attr('height', square_height)
          .attr('rx', 4)
          .attr('ry', 4)
          .attr("stroke", "#010101")
          .attr("stroke-width", "2px")
          .attr('fill', function (d) {
            return d3_color.lab(35, 127 * (d.win_standing - d.lost_standing)/d.total_games, 127 * (d.win_hitting - d.lost_hitting)/d.total_games);
          })
          .on("mouseover", function(d) {
            d3.select(this).attr("fill", function () {
              div.html( 'S: ' +  (100*(d.win_standing - d.lost_standing)/d.total_games).toFixed(2)  + '</br>H: ' + (100*(d.win_hitting - d.lost_hitting)/d.total_games).toFixed(2))
                .style("left", (d3.event.pageX) + "px")
                .style("top", (d3.event.pageY - 50) + "px")
                .style("opacity", 0.9)
                .style("font-family", "monospace");
              return d3_color.lab(70, 127 * (d.win_standing - d.lost_standing) / d.total_games, 127 * (d.win_hitting - d.lost_hitting) / d.total_games);
            });

          })
          .on("mouseout", function(d) {
            d3.select(this).attr("fill", function() {
              return d3_color.lab(35, 127 * (d.win_standing - d.lost_standing)/d.total_games, 127 * (d.win_hitting - d.lost_hitting)/d.total_games);
            });
          })
          .on("click", function(d) {
            create_heatmap(level + 1, d.player_hand);
          });

        var playerHandLabel = d3
          .select('#level-' + level)
          .select("svg")
          .append('g')
          .selectAll(".playerHandLabel")
          .data(csv)
          .enter()
          .filter(function(d) { return d.player_hand.startsWith(starts_with) })
          .append("text")
          .text(function (d) { return d.player_hand; })
          .attr('x', function(d, i) { return Math.trunc(i/10) * square_width + 7/5*square_width })
          .attr('y', 5)
          .attr("font-size", 12)
          .attr("font-type", "bold")
          .style('fill', 'white')
          .attr("writing-mode", "vertical-rl");

        var dealerFaceUpLabel = d3
          .select('#level-' + level)
          .select("svg")
          .append('g')
          .selectAll(".dealerFaceUpLabel")
          .data(csv)
          .enter()
          .filter(function(d) { return d.player_hand.startsWith(starts_with) })
          .append("text")
          .text(function (d) { return d.dealer_up_card; })
          .attr('x', 15)
          .attr('y', function(d, i) { return i % 10 * square_height+ 8/5*square_height; })
          .attr("font-size", 12)
          .style('fill', 'white')
          .attr("font-type", "bold")

      });
    }
    create_heatmap(2, '');

  }
}
