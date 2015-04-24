# NmeaConverter
NmeaConverter OpenCPN Plugin
I wanted dashboard to show the air temperature, but my AirmarPB200 doesn't send the right senteces for this. Now could I hack around in dashboard to get it work, but decided to take an other way.
I made a hard coded plugin to take the temp data from the PB200 (a $WIMDA sentence) and convert this to a $xxMTA sentence wanted by dashboard. When this worked I made it more general useable by adding a kind of spreadsheet art of formula writing.
In principle you can compose every posible nmea sentence, and send timed or after updating the input variables. That is sending every x seconds, or after all variables used in the output are renewed.
This could help to get some picky instruments working. Say converting waypoint to a format the autopilot understands, or routes to a gps that wants a special format.
