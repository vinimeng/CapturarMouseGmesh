lc = 0.3;

Point(1) = {0.210000, 0.102000, 0, lc};
Point(2) = {0.334000, 0.099000, 0, lc};
Point(3) = {0.512000, 0.094000, 0, lc};
Point(4) = {0.738000, 0.094000, 0, lc};
Point(5) = {0.897000, 0.321000, 0, lc};
Point(6) = {0.778000, 0.491000, 0, lc};
Point(7) = {0.560000, 0.499000, 0, lc};
Point(8) = {0.406000, 0.501000, 0, lc};
Point(9) = {0.248000, 0.503000, 0, lc};
Point(10) = {0.142000, 0.499000, 0, lc};
Point(11) = {0.362000, 0.308000, 0, lc};
Point(12) = {0.070000, 0.113000, 0, lc};



// cria linhas
Line(1)={1,2};
Line(2)={2,3};
Line(3)={3,4};
Line(4)={4,5};
Line(5)={5,6};
Line(6)={6,7};
Line(7)={7,8};
Line(8)={8,9};
Line(9)={9,10};
Line(10)={10,11};
Line(11)={11,12};
Line(12)={12,1};



// cria superficie
Curve Loop(1) = {1,2,3,4,5,6,7,8,9,10,11,12};

Plane Surface(1) = {1}; 

Physical Surface (1) = {1};