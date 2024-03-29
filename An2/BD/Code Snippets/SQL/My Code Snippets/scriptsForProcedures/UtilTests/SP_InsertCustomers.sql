USE [MusicShop]
GO
/****** Object:  StoredProcedure [dbo].[SP_InsertCustomers]    Script Date: 12/8/2022 9:38:04 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
ALTER PROCEDURE [dbo].[SP_InsertCustomers] 
	-- Add the parameters for the stored procedure here
	@Rows int
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
	DBCC CHECKIDENT ('Customers', RESEED, 0);
	
	while @Rows > 0
	begin
		INSERT INTO [dbo].[Customers]
			   ([name]
			   ,[password]
			   ,[email]
			   ,[phone]
			   ,[isMusician]
			   ,[birthdate])
		 VALUES
			   ('Nume' + cast(@Rows as nvarchar(50))
			   ,'Parola' + cast(@Rows as nvarchar(50))
			   ,'Email' + cast(@Rows as nvarchar(50))
			   ,'07' + cast((10000000 + @Rows) as char(10))
			   ,'0'
			   ,'2022-02-01');
		set @Rows = @Rows -1
	end
    -- Insert statements for procedure here
	print 'executed InsertUsers' + cast(@Rows as varchar(50))
END
