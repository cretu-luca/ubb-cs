using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using WebApplication2;
using WebApplication2.Models;
using System.Linq;
using System;
using System.Collections;
using System.Collections.Generic;

namespace MyApp.Namespace
{
    public class StudentsForCourseModel : PageModel
    {
        private readonly AppDbContext _context;
        
        public ICollection<Person> Students { get; set; }
        
        public StudentsForCourseModel(AppDbContext context)
        {
            _context = context;
        }
        
        public void OnGet()
        {
            Students = new List<Person>();
        }

        public IActionResult OnPost()
        {
            String username = HttpContext.Session.GetString("username");
            
            String courseName = Request.Form["courseName"];
            Course course = _context.Courses.Where(course => course.CourseName == courseName).FirstOrDefault();
            var participantsIds = course.Participants.Split(",");

            ICollection<Person> persons = _context.Persons.ToList();
            ICollection<Person> students = new List<Person>();
            
            foreach (Person person in persons)
            {
                bool isParticipant = false; 
                
                foreach (String participantId in participantsIds)
                {
                    if (participantId.Trim() == person.Id.ToString())
                    {
                        isParticipant = true;
                    }
                }

                if (isParticipant == true)
                {
                    students.Add(person);
                }
            }
            
            Students = students;
            
            return Page();
        }
    }
}
