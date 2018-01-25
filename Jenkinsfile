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
                // Only say hello if a "greeting" is requested
                expression { env.BRANCH_NAME == 'docs_deploy' }
            }
            steps {
                 sh 'rm -rf /usr/share/nginx/docs.paradigmhyperloop.com/flight-computer/*'
                 sh 'cp -r ./docs/* /usr/share/nginx/docs.paradigmhyperloop.com/flight-computer/'
            }
    }
  }
  post {
    always {
      archive 'docs.zip'
    }
  }
}


