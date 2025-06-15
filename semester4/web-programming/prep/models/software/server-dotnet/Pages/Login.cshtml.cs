using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using System.Text.Json;
using System.Text;

namespace server_dotnet.Pages
{
    public class LoginModel : PageModel
    {
        private readonly HttpClient _httpClient;

        [BindProperty]
        public string Username { get; set; } = "";
        
        public string ErrorMessage { get; set; } = "";

        public LoginModel(IHttpClientFactory httpClientFactory)
        {
            _httpClient = httpClientFactory.CreateClient();
        }

        public void OnGet()
        {
            // Just display the login page
        }

        public async Task<IActionResult> OnPostAsync()
        {
            var loginRequest = new { Username = Username };
            var json = JsonSerializer.Serialize(loginRequest);
            var content = new StringContent(json, Encoding.UTF8, "application/json");

            try
            {
                var response = await _httpClient.PostAsync("http://localhost:5262/Auth/Login", content);
                
                if (response.IsSuccessStatusCode)
                {
                    // Copy cookies from the API response to the current response
                    if (response.Headers.Contains("Set-Cookie"))
                    {
                        foreach (var cookie in response.Headers.GetValues("Set-Cookie"))
                        {
                            Response.Headers.Add("Set-Cookie", cookie);
                        }
                    }
                    return RedirectToPage("/MyProjects");
                }
                else
                {
                    ErrorMessage = "Login failed. User not found.";
                    return Page();
                }
            }
            catch (Exception ex)
            {
                ErrorMessage = $"Login error: {ex.Message}";
                return Page();
            }
        }
    }
} 