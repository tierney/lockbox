#include "db_email_user.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "base/memory/scoped_ptr.h"
#include "base/files/scoped_temp_dir.h"
#include "base/files/file_path.h"
#include "base/file_util.h"
using base::FilePath;
namespace lockbox {
class EmailUserDBTest : public ::testing::Test {
 public:
  EmailUserDBTest() {
    file_util::CreateNewTempDirectory("", &tempdir_);
    email_user_db_.reset(new EmailUserDB(tempdir_.value()));
  }

  virtual ~EmailUserDBTest() {
  }

 protected:
  FilePath tempdir_;
  scoped_ptr<EmailUserDB> email_user_db_;
};

TEST_F(EmailUserDBTest, NonExistTest) {
  EXPECT_EQ("", email_user_db_->GetUser("user@me.com"));
}

TEST_F(EmailUserDBTest, FoundTest) {
  EXPECT_EQ("", email_user_db_->GetUser("user@me.com"));
  EXPECT_TRUE(email_user_db_->SetEmailUser("user@me.com", "UID"));
  EXPECT_EQ("UID", email_user_db_->GetUser("user@me.com"));
}

} // namespace lockbox
