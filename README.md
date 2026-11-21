#SFML Bouncing Ball Simulation

A 2D physics simulation built in C++ using SFML. The project models a ball falling under gravity, bouncing against a floor, and gradually losing energy after each collision.

##Features

-Frame rate independent movement using delta time
-Gravity based acceleration
-Floor collisions using globalbounds()
-Overlap correction to prevent ball from falling through the floor
-Restitution to simulate energy loss after each bounce
-Resting speed threshold to prevent repeated tiny bounces
-Space to pause, R to reset ball

##Controls

SpaceBar for Pausing simulation
R key for Resetting simulation

##Physics Concepts

##Gravity- Increases ball's vertical velocity every frame.

##Position Update- Ball moves according to (velocity * deltatime), using delta time to ensure motion consistency across different frame rates.

##Restitution- Ensures the ball loses energy with each time the ball collides with the floor.

##Resting Speed- Small bounces can continue indefinitely because restituion reduces velocity without ever reaching zero, Resting speed threshold is needed to stop the ball.

#How to Run

1.Open the solution in Visual Studio.
2.Ensure SFML is configured for the project.
3.Build and run the program.



