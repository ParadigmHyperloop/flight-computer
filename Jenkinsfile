pipeline {
  agent any
  stages {
    stage('Build') {
      steps {
        parallel(
          "Build": {
            sh './setup.sh'
            sh 'rm -rf build && mkdir -p build'
            sh 'cd build && ls -lah'
            sh 'cd build && cmake ..'
            sh 'cd build && ls -lah'
            sh 'cd build && pwd'
            sh 'cd build && make -j 12'
          },          
          "Documentation": {
            sh 'doxygen ./doxygen-config'
            sh 'zip -r docs.zip docs'
          }
        )
      }
    }
    stage('Test') {
      steps {
         sh 'cd build && make check'
      }
    }
    stage ('Deploy') {
            when {
              expression { env.BRANCH_NAME == 'docs_deploy' }
            }
            steps {
              sh 'rm -rf ' + env.JENKINS_HOME + '/userContent/docs/flight-computer/*'
              sh 'cp -r ./docs/* ' + env.JENKINS_HOME + '/userContent/docs/flight-computer/'
            }
    }
  }
  post {
    always {
      archive 'docs.zip'
    }
  }
}


