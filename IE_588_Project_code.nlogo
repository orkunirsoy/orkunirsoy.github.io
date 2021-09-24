globals
[
  spread-in-network-v ;; infection rate in network for vaccinated people
  spread-random-v     ;; spread rate in random interactions for vaccinated people
  spread-in-network   ;; infection rate in network
  spread-random       ;; spread rate in random interactions
  mean-of-random-interactions ;; mean of random interaction number
  sd-of-random-interactions ;; sd of random interaction number
  recovery-time ;; how long does it takes to recover from infection
]


turtles-own
[
  sick?  ;; true if the turtle is infected, false otherwise
  sick-time  ;; Time passed since the turtle is infected
  vaccinated? ;; true if the turtle is vaccinated
  recovered? ;; true if a turtle has recovered from the disease
  random-interaction-number ;; with how many people the turtle interacts per tick (normally distributed among turtles with mean and sd)
  next-step-sick? ;; true if turtle infected in that tick
  vac-opinion ;; 0 is the ones who are up for that while 1 represents the ones that don't want to use vaccination

]

to setup
  clear-all
  reset-ticks
  ask patches [set pcolor 86]

  set mean-of-random-interactions mean-random-interaction-number
  set sd-of-random-interactions sd-of-random-interaction-number
  set recovery-time 8
  set spread-in-network-v 0.9 * (1 - 0.97)
  set spread-random-v     0.083 * 0.03
  set spread-in-network   0.9
  set spread-random       0.083

  setup-nodes
  setup-network

  ask links
    [ set color white]
end


to setup-nodes
  set-default-shape turtles "circle"
  crt number-of-nodes
    [
      setxy (random-xcor * 0.9) (random-ycor * 0.9)
      set sick? false
      set vaccinated? false
      set recovered? false
      set sick-time 0
      set next-step-sick? false
      set vac-opinion random-float 1
      set random-interaction-number round (random-normal mean-of-random-interactions sd-of-random-interactions)
      if random-interaction-number < 0 [ set random-interaction-number 0]
      if random-interaction-number > number-of-nodes [set random-interaction-number number-of-nodes]
      set color red
      set size  0.5
    ]
  ask n-of round ((vaccinated-percentage / 100) * number-of-nodes) turtles [set vaccinated? true
                                                                    set size 1]

  ask n-of 1 turtles
  [set sick? true
   set color green
  ]

end

to setup-network
  let num-links (average-node-degree * number-of-nodes) / 2
  while [count links < num-links ]
  [
    ask one-of turtles
    [
      let choice (min-one-of (other turtles with [not link-neighbor? myself])
                   [distance myself])
      if choice != nobody [ create-link-with choice ]
    ]
  ]
  ; make the network look a little prettier
  repeat 10
  [
    layout-spring turtles links 0.3 (world-width / (sqrt number-of-nodes)) 1
  ]
end


to go
  ask turtles [update-info]
  ask turtles with [sick? = false and recovered? = false] [consider-vaccination]
  ask turtles [update-wellbeing]
  tick
  if (ticks > RunLength) [stop]
end

to consider-vaccination
  let sick-link-known count link-neighbors with [sick? = true]
  if vac-opinion < (sick-link-known * (count turtles with [sick? = true] / count turtles))
  [set vaccinated? true
   set size 1
  ]

end

to update-info
  let sick-link-known count link-neighbors with [sick? = true and sick-time >= 4]
  let sick-link-unknown count link-neighbors with [sick? = true and sick-time < 4]
  let possible n-of random-interaction-number turtles
  let possible-sick count possible with [sick? = true]

  if (sick? = false) and (recovered? = false) [
     ifelse (vaccinated? = true)
      [ repeat sick-link-known [ if random-float 1 < spread-in-network-v / 2 [set next-step-sick? true]]
        repeat sick-link-unknown [ if random-float 1 < spread-in-network-v [set next-step-sick? true]]
        repeat possible-sick [ if random-float 1 < spread-random-v [set next-step-sick? true]]
      ]
      [ repeat sick-link-known [ if random-float 1 < spread-in-network / 2  [set next-step-sick? true]]
        repeat sick-link-unknown [ if random-float 1 < spread-in-network   [set next-step-sick? true]]
        repeat possible-sick [ if random-float 1 < spread-random [set next-step-sick? true]]
      ]


  ]
end


to update-wellbeing
  if (sick? = true) [ set sick-time sick-time + 1]

  if (next-step-sick? = true) [set sick? true
                               set color green
                               set next-step-sick? false]


  if sick-time > recovery-time [set sick? false
                                set recovered? true
                                set color yellow
                                set sick-time  0]
end
@#$#@#$#@
GRAPHICS-WINDOW
917
10
1361
455
-1
-1
13.212121212121213
1
10
1
1
1
0
1
1
1
-16
16
-16
16
0
0
1
ticks
30.0

INPUTBOX
9
14
145
74
number-of-nodes
1000.0
1
0
Number

INPUTBOX
10
80
145
140
average-node-degree
5.0
1
0
Number

BUTTON
153
14
292
74
NIL
setup
NIL
1
T
OBSERVER
NIL
NIL
NIL
NIL
1

BUTTON
153
81
290
139
NIL
go
T
1
T
OBSERVER
NIL
NIL
NIL
NIL
1

INPUTBOX
9
147
146
207
RunLength
200.0
1
0
Number

SLIDER
153
147
331
180
vaccinated-percentage
vaccinated-percentage
0.1
99.9
68.7
0.1
1
NIL
HORIZONTAL

PLOT
351
10
648
173
Percentage of sick people at the moment
NIL
NIL
0.0
10.0
0.0
1.0
true
false
"" ""
PENS
"default" 1.0 0 -16777216 true "" "plot count turtles with [sick? = true] * 100 / number-of-nodes"

PLOT
32
288
587
503
Percentage of people caught and recovered from disease
NIL
NIL
0.0
10.0
0.0
10.0
true
true
"" ""
PENS
"infected" 1.0 0 -16777216 true "" "plot count turtles with [recovered? = true] * 100 / count turtles"
"infected_no_vac" 1.0 0 -7500403 true "" "plot count turtles with [recovered? = true and vaccinated? = false] * 100 / count turtles with [vaccinated? = false]"
"infected_vac" 1.0 0 -2674135 true "" "plot count turtles with [recovered? = true and vaccinated? = true] * 100 / count turtles with [vaccinated? = true]"

INPUTBOX
152
193
329
253
mean-random-interaction-number
5.0
1
0
Number

INPUTBOX
344
193
499
253
sd-of-random-interaction-number
2.0
1
0
Number

PLOT
616
185
816
335
plot 1
NIL
NIL
0.0
10.0
0.0
10.0
true
false
"" ""
PENS
"default" 1.0 0 -16777216 true "" "plot count turtles with [vaccinated? = true]"

@#$#@#$#@
## WHAT IS IT?

This section could give a general understanding of what the model is trying to show or explain.

## HOW IT WORKS

This section could explain what rules the agents use to create the overall behavior of the model.

## HOW TO USE IT

This section could explain how to use the model, including a description of each of the items in the interface tab.

## THINGS TO NOTICE

This section could give some ideas of things for the user to notice while running the model.

## THINGS TO TRY

This section could give some ideas of things for the user to try to do (move sliders, switches, etc.) with the model.

## EXTENDING THE MODEL

This section could give some ideas of things to add or change in the procedures tab to make the model more complicated, detailed, accurate, etc.

## NETLOGO FEATURES

This section could point out any especially interesting or unusual features of NetLogo that the model makes use of, particularly in the Procedures tab.  It might also point out places where workarounds were needed because of missing features.

## RELATED MODELS

This section could give the names of models in the NetLogo Models Library or elsewhere which are of related interest.

## CREDITS AND REFERENCES

This section could contain a reference to the model's URL on the web if it has one, as well as any other necessary credits or references.
@#$#@#$#@
default
true
0
Polygon -7500403 true true 150 5 40 250 150 205 260 250

airplane
true
0
Polygon -7500403 true true 150 0 135 15 120 60 120 105 15 165 15 195 120 180 135 240 105 270 120 285 150 270 180 285 210 270 165 240 180 180 285 195 285 165 180 105 180 60 165 15

arrow
true
0
Polygon -7500403 true true 150 0 0 150 105 150 105 293 195 293 195 150 300 150

box
false
0
Polygon -7500403 true true 150 285 285 225 285 75 150 135
Polygon -7500403 true true 150 135 15 75 150 15 285 75
Polygon -7500403 true true 15 75 15 225 150 285 150 135
Line -16777216 false 150 285 150 135
Line -16777216 false 150 135 15 75
Line -16777216 false 150 135 285 75

bug
true
0
Circle -7500403 true true 96 182 108
Circle -7500403 true true 110 127 80
Circle -7500403 true true 110 75 80
Line -7500403 true 150 100 80 30
Line -7500403 true 150 100 220 30

butterfly
true
0
Polygon -7500403 true true 150 165 209 199 225 225 225 255 195 270 165 255 150 240
Polygon -7500403 true true 150 165 89 198 75 225 75 255 105 270 135 255 150 240
Polygon -7500403 true true 139 148 100 105 55 90 25 90 10 105 10 135 25 180 40 195 85 194 139 163
Polygon -7500403 true true 162 150 200 105 245 90 275 90 290 105 290 135 275 180 260 195 215 195 162 165
Polygon -16777216 true false 150 255 135 225 120 150 135 120 150 105 165 120 180 150 165 225
Circle -16777216 true false 135 90 30
Line -16777216 false 150 105 195 60
Line -16777216 false 150 105 105 60

car
false
0
Polygon -7500403 true true 300 180 279 164 261 144 240 135 226 132 213 106 203 84 185 63 159 50 135 50 75 60 0 150 0 165 0 225 300 225 300 180
Circle -16777216 true false 180 180 90
Circle -16777216 true false 30 180 90
Polygon -16777216 true false 162 80 132 78 134 135 209 135 194 105 189 96 180 89
Circle -7500403 true true 47 195 58
Circle -7500403 true true 195 195 58

circle
false
0
Circle -7500403 true true 0 0 300

circle 2
false
0
Circle -7500403 true true 0 0 300
Circle -16777216 true false 30 30 240

cow
false
0
Polygon -7500403 true true 200 193 197 249 179 249 177 196 166 187 140 189 93 191 78 179 72 211 49 209 48 181 37 149 25 120 25 89 45 72 103 84 179 75 198 76 252 64 272 81 293 103 285 121 255 121 242 118 224 167
Polygon -7500403 true true 73 210 86 251 62 249 48 208
Polygon -7500403 true true 25 114 16 195 9 204 23 213 25 200 39 123

cylinder
false
0
Circle -7500403 true true 0 0 300

dot
false
0
Circle -7500403 true true 90 90 120

face happy
false
0
Circle -7500403 true true 8 8 285
Circle -16777216 true false 60 75 60
Circle -16777216 true false 180 75 60
Polygon -16777216 true false 150 255 90 239 62 213 47 191 67 179 90 203 109 218 150 225 192 218 210 203 227 181 251 194 236 217 212 240

face neutral
false
0
Circle -7500403 true true 8 7 285
Circle -16777216 true false 60 75 60
Circle -16777216 true false 180 75 60
Rectangle -16777216 true false 60 195 240 225

face sad
false
0
Circle -7500403 true true 8 8 285
Circle -16777216 true false 60 75 60
Circle -16777216 true false 180 75 60
Polygon -16777216 true false 150 168 90 184 62 210 47 232 67 244 90 220 109 205 150 198 192 205 210 220 227 242 251 229 236 206 212 183

fish
false
0
Polygon -1 true false 44 131 21 87 15 86 0 120 15 150 0 180 13 214 20 212 45 166
Polygon -1 true false 135 195 119 235 95 218 76 210 46 204 60 165
Polygon -1 true false 75 45 83 77 71 103 86 114 166 78 135 60
Polygon -7500403 true true 30 136 151 77 226 81 280 119 292 146 292 160 287 170 270 195 195 210 151 212 30 166
Circle -16777216 true false 215 106 30

flag
false
0
Rectangle -7500403 true true 60 15 75 300
Polygon -7500403 true true 90 150 270 90 90 30
Line -7500403 true 75 135 90 135
Line -7500403 true 75 45 90 45

flower
false
0
Polygon -10899396 true false 135 120 165 165 180 210 180 240 150 300 165 300 195 240 195 195 165 135
Circle -7500403 true true 85 132 38
Circle -7500403 true true 130 147 38
Circle -7500403 true true 192 85 38
Circle -7500403 true true 85 40 38
Circle -7500403 true true 177 40 38
Circle -7500403 true true 177 132 38
Circle -7500403 true true 70 85 38
Circle -7500403 true true 130 25 38
Circle -7500403 true true 96 51 108
Circle -16777216 true false 113 68 74
Polygon -10899396 true false 189 233 219 188 249 173 279 188 234 218
Polygon -10899396 true false 180 255 150 210 105 210 75 240 135 240

house
false
0
Rectangle -7500403 true true 45 120 255 285
Rectangle -16777216 true false 120 210 180 285
Polygon -7500403 true true 15 120 150 15 285 120
Line -16777216 false 30 120 270 120

leaf
false
0
Polygon -7500403 true true 150 210 135 195 120 210 60 210 30 195 60 180 60 165 15 135 30 120 15 105 40 104 45 90 60 90 90 105 105 120 120 120 105 60 120 60 135 30 150 15 165 30 180 60 195 60 180 120 195 120 210 105 240 90 255 90 263 104 285 105 270 120 285 135 240 165 240 180 270 195 240 210 180 210 165 195
Polygon -7500403 true true 135 195 135 240 120 255 105 255 105 285 135 285 165 240 165 195

line
true
0
Line -7500403 true 150 0 150 300

line half
true
0
Line -7500403 true 150 0 150 150

pentagon
false
0
Polygon -7500403 true true 150 15 15 120 60 285 240 285 285 120

person
false
0
Circle -7500403 true true 110 5 80
Polygon -7500403 true true 105 90 120 195 90 285 105 300 135 300 150 225 165 300 195 300 210 285 180 195 195 90
Rectangle -7500403 true true 127 79 172 94
Polygon -7500403 true true 195 90 240 150 225 180 165 105
Polygon -7500403 true true 105 90 60 150 75 180 135 105

plant
false
0
Rectangle -7500403 true true 135 90 165 300
Polygon -7500403 true true 135 255 90 210 45 195 75 255 135 285
Polygon -7500403 true true 165 255 210 210 255 195 225 255 165 285
Polygon -7500403 true true 135 180 90 135 45 120 75 180 135 210
Polygon -7500403 true true 165 180 165 210 225 180 255 120 210 135
Polygon -7500403 true true 135 105 90 60 45 45 75 105 135 135
Polygon -7500403 true true 165 105 165 135 225 105 255 45 210 60
Polygon -7500403 true true 135 90 120 45 150 15 180 45 165 90

square
false
0
Rectangle -7500403 true true 30 30 270 270

square 2
false
0
Rectangle -7500403 true true 30 30 270 270
Rectangle -16777216 true false 60 60 240 240

star
false
0
Polygon -7500403 true true 151 1 185 108 298 108 207 175 242 282 151 216 59 282 94 175 3 108 116 108

target
false
0
Circle -7500403 true true 0 0 300
Circle -16777216 true false 30 30 240
Circle -7500403 true true 60 60 180
Circle -16777216 true false 90 90 120
Circle -7500403 true true 120 120 60

tree
false
0
Circle -7500403 true true 118 3 94
Rectangle -6459832 true false 120 195 180 300
Circle -7500403 true true 65 21 108
Circle -7500403 true true 116 41 127
Circle -7500403 true true 45 90 120
Circle -7500403 true true 104 74 152

triangle
false
0
Polygon -7500403 true true 150 30 15 255 285 255

triangle 2
false
0
Polygon -7500403 true true 150 30 15 255 285 255
Polygon -16777216 true false 151 99 225 223 75 224

truck
false
0
Rectangle -7500403 true true 4 45 195 187
Polygon -7500403 true true 296 193 296 150 259 134 244 104 208 104 207 194
Rectangle -1 true false 195 60 195 105
Polygon -16777216 true false 238 112 252 141 219 141 218 112
Circle -16777216 true false 234 174 42
Rectangle -7500403 true true 181 185 214 194
Circle -16777216 true false 144 174 42
Circle -16777216 true false 24 174 42
Circle -7500403 false true 24 174 42
Circle -7500403 false true 144 174 42
Circle -7500403 false true 234 174 42

turtle
true
0
Polygon -10899396 true false 215 204 240 233 246 254 228 266 215 252 193 210
Polygon -10899396 true false 195 90 225 75 245 75 260 89 269 108 261 124 240 105 225 105 210 105
Polygon -10899396 true false 105 90 75 75 55 75 40 89 31 108 39 124 60 105 75 105 90 105
Polygon -10899396 true false 132 85 134 64 107 51 108 17 150 2 192 18 192 52 169 65 172 87
Polygon -10899396 true false 85 204 60 233 54 254 72 266 85 252 107 210
Polygon -7500403 true true 119 75 179 75 209 101 224 135 220 225 175 261 128 261 81 224 74 135 88 99

wheel
false
0
Circle -7500403 true true 3 3 294
Circle -16777216 true false 30 30 240
Line -7500403 true 150 285 150 15
Line -7500403 true 15 150 285 150
Circle -7500403 true true 120 120 60
Line -7500403 true 216 40 79 269
Line -7500403 true 40 84 269 221
Line -7500403 true 40 216 269 79
Line -7500403 true 84 40 221 269

x
false
0
Polygon -7500403 true true 270 75 225 30 30 225 75 270
Polygon -7500403 true true 30 75 75 30 270 225 225 270
@#$#@#$#@
NetLogo 6.0.4
@#$#@#$#@
@#$#@#$#@
@#$#@#$#@
<experiments>
  <experiment name="experiment" repetitions="100" runMetricsEveryStep="false">
    <setup>setup</setup>
    <go>go</go>
    <timeLimit steps="200"/>
    <metric>count turtles with [recovered? = true ] / count turtles</metric>
    <enumeratedValueSet variable="number-of-nodes">
      <value value="1000"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="mean-random-interaction-number">
      <value value="5"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="vaccinated-percentage">
      <value value="1"/>
      <value value="5"/>
      <value value="25"/>
      <value value="50"/>
      <value value="75"/>
      <value value="95"/>
      <value value="99"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="sd-of-random-interaction-number">
      <value value="2"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="average-node-degree">
      <value value="5"/>
    </enumeratedValueSet>
    <enumeratedValueSet variable="RunLength">
      <value value="200"/>
    </enumeratedValueSet>
  </experiment>
</experiments>
@#$#@#$#@
@#$#@#$#@
default
0.0
-0.2 0 0.0 1.0
0.0 1 1.0 0.0
0.2 0 0.0 1.0
link direction
true
0
Line -7500403 true 150 150 90 180
Line -7500403 true 150 150 210 180
@#$#@#$#@
0
@#$#@#$#@
