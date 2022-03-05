# GTK4_Mystery
Unusual behavior in GTK4 with CSS overrides on progress bar widgets.

As I was learning GTK3, I wrote a small test program to observe how CSS overrides
worked with various widgets such as progress bars.  My simple program uses CSS
overrides to change the width and color of the progress bar and works as expected
in GTK version three.

When I continued with my self-education process of learing the new version of GTK
(version four), I attemped to migrate my program to GTK4 and again run the 
program to observe its behavior.  When I ran the program, the CSS overrides for
each progress bar widget were ignored and the program display two generic
progress bars.  When I added a bit of temporary code to associate a progress bar
override to the display, the override did work but affected both progress bars
in a global manner. I could not individualize the CSS overrides.

Strangely, I could apply a CSS override to a label widget and to the text of a
button widget in my GTK4 version of the program.  For some reason, the progress
bar widgets would not react to the individual cSS overrides.

Both the GTK3 version and GTK4 versions of the sample application will be
uploaded if anyone wants to test out this scenrio.

Regards,

Craig
