using Microsoft.EntityFrameworkCore;
using asp_dotnet.Model;

namespace asp_dotnet.Repository
{
    public class BaseRepository<T> : IBaseRepository<T> where T : class
    {
        protected ApplicationDatabaseContext context;
        private DbSet<T> entities;

        public BaseRepository(ApplicationDatabaseContext context)
        {
            this.context = context;
            this.entities = context.Set<T>();
        }
        public async Task<IEnumerable<T>> GetAllAsync()
        {
            return await entities.ToListAsync();
        }
        public async Task<T> GetByIdAsync(int id)
        {
            return await entities.FindAsync(id);
        }
        public async Task<T> AddAsync(T entity)
        {
            await this.entities.AddAsync(entity);
            await this.context.SaveChangesAsync();
            return entity;
        }
        public async Task UpdateAsync(T entity)
        {
            this.context.Entry(entity).State = EntityState.Modified;
            await this.context.SaveChangesAsync();
        }
        public async Task DeleteAsync(int id)
        {
            var entity = await entities.FindAsync(id);
            if (entity != null)
            {
                entities.Remove(entity);
                await context.SaveChangesAsync();
            }
        }
    }
}