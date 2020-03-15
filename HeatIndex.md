# Heat Index

See https://www.wpc.ncep.noaa.gov/html/heatindex.shtml

```javascript
// Heat index computed using air temperature F and RH%
function heat1(HeatIndex){
    if(HeatIndex.RHumidity.value > 100){
        alert("Relative humidity cannot exceed 100%.");
    }
    else if (HeatIndex.RHumidity.value < 0) {
        alert("Relative humidity cannot be less than 0%.");
    }
    else if (HeatIndex.tempair.value <= 40.0) {
        var hi = HeatIndex.tempair.value;
    }
    else {
        var hitemp = 61.0+((HeatIndex.tempair.value-68.0)*1.2)+(HeatIndex.RHumidity.value*0.094);
        var fptemp = parseFloat(HeatIndex.tempair.value);
        var hifinal = 0.5*(fptemp+hitemp);

        if(hifinal > 79.0){
            var hi = -42.379+2.04901523*HeatIndex.tempair.value+10.14333127*HeatIndex.RHumidity.value-0.22475541*HeatIndex.tempair.value*HeatIndex.RHumidity.value-6.83783*(Math.pow(10, -3))*(Math.pow(HeatIndex.tempair.value, 2))-5.481717*(Math.pow(10, -2))*(Math.pow(HeatIndex.RHumidity.value, 2))+1.22874*(Math.pow(10, -3))*(Math.pow(HeatIndex.tempair.value, 2))*HeatIndex.RHumidity.value+8.5282*(Math.pow(10, -4))*HeatIndex.tempair.value*(Math.pow(HeatIndex.RHumidity.value, 2))-1.99*(Math.pow(10, -6))*(Math.pow(HeatIndex.tempair.value, 2))*(Math.pow(HeatIndex.RHumidity.value,2));
            if((HeatIndex.RHumidity.value <= 13) && (HeatIndex.tempair.value >= 80.0) && (HeatIndex.tempair.value <= 112.0)) {
                var adj1 = (13.0-HeatIndex.RHumidity.value)/4.0;
                var adj2 = Math.sqrt((17.0-Math.abs(HeatIndex.tempair.value-95.0))/17.0);
                var adj = adj1 * adj2;
                var hi = hi - adj;
            }
            else if ((HeatIndex.RHumidity.value > 85.0) && (HeatIndex.tempair.value >= 80.0) && (HeatIndex.tempair.value <= 87.0)) {
                var adj1 = (HeatIndex.RHumidity.value-85.0)/10.0;
                var adj2 = (87.0-HeatIndex.tempair.value)/5.0;
                var adj = adj1 * adj2;
                var hi = hi + adj;
            }
        }
        else{
            var hi = hifinal;
        }
    }
    HeatIndex.heatindex.value = Math.round(hi) + " F" +  " / " + Math.round((hi - 32) * .556) + " C";
    var tempc2 = (HeatIndex.tempair.value - 32) * .556;
    var rh2 = 1 - HeatIndex.RHumidity.value/100;
    var tdpc2 = tempc2 - (((14.55 + .114*tempc2)*rh2) + (Math.pow(((2.5 + .007*tempc2)*rh2), 3)) + ((15.9 + .117*tempc2))*(Math.pow(rh2, 14)));
   
}
```