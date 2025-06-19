using Microsoft.EntityFrameworkCore;
using WebApplication5;
using WebApplication5.Hubs;

var builder = WebApplication.CreateBuilder(args);

builder.Services.AddRazorPages();
builder.Services.AddSignalR();

builder.Services.AddDbContext<AppDbContext>(options => 
    options.UseMySql("server=localhost;port=3306;database=HotelReservation;user=root;password=", 
        ServerVersion.AutoDetect("server=localhost;port=3306;database=HotelReservation;user=root;password=")));

builder.Services.AddDistributedMemoryCache();
builder.Services.AddSession(options =>
{
    options.IdleTimeout = TimeSpan.FromMinutes(30);
    options.Cookie.HttpOnly = true;
    options.Cookie.IsEssential = true;
});

var app = builder.Build();

if (!app.Environment.IsDevelopment())
{
    app.UseExceptionHandler("/Error");
    app.UseHsts();
}

app.MapGet("/", async context =>
{
    context.Response.Redirect("/Login");
});

app.UseHttpsRedirection();
app.UseStaticFiles();

app.UseRouting();

app.UseAuthorization();

app.UseSession();
app.MapRazorPages();
app.MapHub<ReservationHub>("/reservationHub");

app.Run();