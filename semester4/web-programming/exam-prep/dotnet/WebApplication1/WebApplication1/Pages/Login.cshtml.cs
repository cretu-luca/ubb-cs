using System.Diagnostics;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;

namespace MyApp.Namespace
{
    public class LoginModel : PageModel
    {
        public void OnGet()
        {
        }

        public void OnPost()
        {
            String username = Request.Form["username"];
            
            if (!string.IsNullOrEmpty(username))
            {
                HttpContext.Session.SetString("username", username);
            }
        }
    }
}
