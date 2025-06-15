using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using WebApplication2;
using WebApplication2.Models;

namespace MyApp.Namespace
{
    public class CoursesForStudentModel : PageModel
    { 
        private readonly AppDbContext _context;
        public ICollection<Course> Courses { get; set; }
        
        public CoursesForStudentModel(AppDbContext context)
        {
            _context = context;
        }
        
        public void OnGet()
        {
            Courses = new List<Course>();
        }

        public IActionResult OnPost()
        {
            String username = HttpContext.Session.GetString("username");
            String studentName = Request.Form["studentName"];
            
            Person student = _context.Persons.Where(s => s.Name == studentName).FirstOrDefault();
            int studentId = student.Id;

            ICollection<Course> courses = _context.Courses.ToList();
            ICollection<Course> coursesToAdd = new List<Course>();
            
            foreach (Course course in courses)
            {
                bool isInCourse = false;
                
                String participantsIds = course.Participants; 
                List<String> participantsIdsList = participantsIds.Split(',').ToList();

                foreach (String participantId in participantsIdsList)
                {
                    if (participantId.Trim() == studentId.ToString())
                    {
                        isInCourse = true;
                    }
                }
                
                if (isInCourse)
                    coursesToAdd.Add(course);
            }
            
            Courses = coursesToAdd;
            
            return Page();
        }
    }
}
