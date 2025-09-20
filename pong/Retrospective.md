## Retrospective - Belows are my personal feeling about this project and what I will do for further project
### What went well
- Even though my initial code was messy, the functionality worked, which gave me confidence to keep going.  
- After finishing a first pass, I spent time refactoring to reduce coupling and apply design patterns (e.g. Strategy Pattern for AI controllers).  
- I realized I could cut one third of my code by reorganizing responsibilities.
### What didn’t go well
- At the start, I often felt fear and uncertainty because I had no mental model of how to structure the code.  
- I failed to implement paddle deflection based on hit position. My attempt even broke existing functionality, showing I hadn’t separated logics of code properly.  
- I rushed into writing collision and ball reset mechanics without thinking them through, which made the code fragile.  
- Because I got interrupted and worked inconsistently, the project dragged on and I lost motivation to clean up messy parts.
### Lessons learned
- Always separate rendering from logic early. This drastically reduces code mess.  
- Don’t rush into implementation when the mechanic is unclear. Sketch it out or look for references first.  
- Keep the habit of refactoring after a first functional version — it’s the best way to practice design patterns in real code.  
- For extensible behavior (like AI), Strategy pattern with injection works very well.
### Next steps
- For Breakout, I want to:
  - Practice logic/render separation from the beginning.
  - Focus on implementing clear gameplay mechanics.
  - Try using the Observer pattern for a menu system.
- General reminders:
  - Avoid magic numbers by using constants/bounds.
  - Look up references if I don’t know how to implement a mechanic instead of “just hacking it.”