//Frida Dynamic instrumentation js file written to catch data sended intent with putExtra function

console.log("Script loaded successfully ");
Java.perform(function x() {
    console.log("Inside java perform function");
	var intenttttt = Java.use("android.content.Intent");
	intenttttt.putExtra.overload('java.lang.String','java.lang.String').implementation = function(var0,var1) {
        console.log("GET value: " + var1);
        return this;
    };
});
